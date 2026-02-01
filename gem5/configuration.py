import m5
import argparse

from m5.objects import System, SrcClockDomain, VoltageDomain, Root
from m5.objects import RiscvO3CPU, Cache, AddrRange, SEWorkload, Process
from m5.objects import MemCtrl, DDR3_1600_8x8, SystemXBar, L2XBar
from m5.objects import RiscvISA
from m5.objects import *

parser = argparse.ArgumentParser()

parser.add_argument(
    "--bin",
    default="",
    type=str
)
parser.add_argument(
    "--vlen",
    default=256,
    type=int
)
args = parser.parse_args()


bin = args.bin
vlen = args.vlen

class L1Cache(Cache):
    assoc = 2
    tag_latency = 2
    data_latency = 2
    response_latency = 2
    mshrs = 4
    tgts_per_mshr = 20

    def connectCPU(self, cpu):
        # need to define this in a base class!
        raise NotImplementedError
    
    def connectBus(self, bus):
        self.mem_side = bus.cpu_side_ports

class L1ICache(L1Cache):
    size = '32kB'

    def connectCPU(self, cpu):
        self.cpu_side = cpu.icache_port

class L1DCache(L1Cache):
    size = '32kB'

    def connectCPU(self, cpu):
        self.cpu_side = cpu.dcache_port

class L2Cache(Cache):
    size = '256kB'
    assoc = 8
    tag_latency = 20
    data_latency = 20
    response_latency = 20
    mshrs = 20
    tgts_per_mshr = 12

    def connectCPUSideBus(self, bus):
        self.cpu_side = bus.mem_side_ports

    def connectMemSideBus(self, bus):
        self.mem_side = bus.cpu_side_ports


system = System()
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('8192MB')]

system.cpu = RiscvO3CPU()

# Create the L1 caches
system.cpu.icache = L1ICache()
system.cpu.dcache = L1DCache()

# Connect the caches to the CPU
system.cpu.icache.connectCPU(system.cpu)
system.cpu.dcache.connectCPU(system.cpu)

system.l2bus = L2XBar()

system.cpu.icache.connectBus(system.l2bus)
system.cpu.dcache.connectBus(system.l2bus)

system.l2cache = L2Cache()
system.l2cache.connectCPUSideBus(system.l2bus)

system.membus = SystemXBar()
system.l2cache.connectMemSideBus(system.membus)

system.cpu.createInterruptController()

system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

system.cpu.isa = RiscvISA(vlen=vlen)

system.workload = SEWorkload.init_compatible(bin)

process = Process()
process.cmd = [bin]
system.cpu.workload = process
system.cpu.createThreads()

system.cpu.fetchWidth = 6
system.cpu.decodeWidth = 2
system.cpu.issueWidth = 4
system.cpu.renameWidth = 4
system.cpu.commitWidth = 6
system.cpu.commitToRenameDelay = 1
system.cpu.numIQEntries = 48
system.cpu.wbWidth = 8
system.cpu.dispatchWidth = 2

class Int_ALU(FUDesc):
    opList = [
        OpDesc(opClass="IntAlu", opLat=3, pipelined=True)
    ]
    count = 1

class Int_Mult_Unit(FUDesc):
    opList = [
        OpDesc(opClass="IntMult", opLat=3, pipelined=True),
    ]
    count = 1

class Int_Div_Unit(FUDesc):
    opList = [
        OpDesc(opClass="IntDiv", opLat=13, pipelined=False),
    ]
    count = 1

class FP_ALU_Unit(FUDesc):
    opList = [
        OpDesc(opClass="FloatAdd",  opLat=4, pipelined=True),
        OpDesc(opClass="FloatCmp",  opLat=4, pipelined=True),
        OpDesc(opClass="FloatCvt",  opLat=4, pipelined=True),
        OpDesc(opClass="FloatMisc", opLat=4, pipelined=True)
    ]
    count = 1

class FP_Mult_Unit(FUDesc):
    opList = [
        OpDesc(opClass="FloatMult",    opLat=4, pipelined=True),
        OpDesc(opClass="FloatMultAcc", opLat=5, pipelined=True)
    ]
    count = 1

class FP_Div_Unit(FUDesc):
    opList = [
        OpDesc(opClass="FloatDiv",  opLat=16, pipelined=False),
        OpDesc(opClass="FloatSqrt", opLat=26, pipelined=False),
    ]
    count = 1

class LSU(FUDesc):
    opList = [
        OpDesc(opClass="MemWrite",      opLat=3, pipelined=True),
        OpDesc(opClass="MemRead",       opLat=1, pipelined=True),
        OpDesc(opClass="FloatMemWrite", opLat=3, pipelined=True),
        OpDesc(opClass="FloatMemRead",  opLat=1, pipelined=True),
    ]
    count = 1

class RVV_Int_ALU(FUDesc):
    opList = [
        OpDesc(opClass="SimdConfig",    opLat=1, pipelined=True),
        OpDesc(opClass="SimdAlu",       opLat=7, pipelined=True),
        OpDesc(opClass="SimdAdd",       opLat=7, pipelined=True),
        OpDesc(opClass="SimdCvt",       opLat=7, pipelined=True),
        OpDesc(opClass="SimdReduceAlu", opLat=4, pipelined=True),
        OpDesc(opClass="SimdReduceCmp", opLat=4, pipelined=True),
        OpDesc(opClass="SimdReduceAdd", opLat=8, pipelined=True),
    ]
    count = 1

class RVV_Int_Mult_Unit(FUDesc):
    opList = [
        OpDesc(opClass="SimdMult",    opLat=6, pipelined=True),
        OpDesc(opClass="SimdMultAcc", opLat=8, pipelined=True),
    ]
    count = 1

class RVV_Int_Div_Unit(FUDesc):
    opList = [
        OpDesc(opClass="SimdDiv", opLat=35, pipelined=False)
    ]
    count = 1

class RVV_Misc_Unit(FUDesc):
    opList = [
        OpDesc(opClass="SimdExt",  opLat=4, pipelined=True),
        OpDesc(opClass="SimdCmp",  opLat=4, pipelined=True),
        OpDesc(opClass="SimdMisc", opLat=4, pipelined=True),
    ]
    count = 1

class RVV_FP_ALU(FUDesc):
    opList = [
        OpDesc(opClass="SimdFloatAlu",       opLat=1, pipelined=True),
        OpDesc(opClass="SimdFloatAdd",       opLat=17, pipelined=True),
        OpDesc(opClass="SimdFloatCmp",       opLat=17, pipelined=True),
        OpDesc(opClass="SimdFloatExt",       opLat=17, pipelined=True),
        OpDesc(opClass="SimdFloatMisc",      opLat=21, pipelined=True),
        OpDesc(opClass="SimdFloatCvt",       opLat=17, pipelined=True),
        OpDesc(opClass="SimdFloatReduceAdd", opLat=8,  pipelined=True),
        OpDesc(opClass="SimdFloatReduceCmp", opLat=12, pipelined=True),
        OpDesc(opClass="SimdShift",          opLat=4, pipelined=True),
    ]
    count = 1

class RVV_FP_Mult_Unit(FUDesc):
    opList = [
        OpDesc(opClass="SimdFloatMult",    opLat=6, pipelined=True),
        OpDesc(opClass="SimdFloatMultAcc", opLat=8, pipelined=True),
        OpDesc(opClass="SimdFloatMatMultAcc")
    ]
    count = 1

class RVV_FP_Div_Unit(FUDesc):
    opList = [
        OpDesc(opClass="SimdFloatDiv",  opLat=120, pipelined=False),
        OpDesc(opClass="SimdFloatSqrt", opLat=140, pipelined=False),
    ]
    count = 1

class RVV_LSU(FUDesc):
    opList = [
        OpDesc(opClass="SimdUnitStrideStore",              opLat=6, pipelined=True),
        OpDesc(opClass="SimdStridedLoad",                  opLat=4, pipelined=True),
        OpDesc(opClass="SimdIndexedLoad",                  opLat=6, pipelined=True),
        OpDesc(opClass="SimdWholeRegisterLoad",            opLat=6, pipelined=True),
        OpDesc(opClass="SimdUnitStrideMaskLoad",           opLat=6, pipelined=True),
        OpDesc(opClass="SimdUnitStrideFaultOnlyFirstLoad", opLat=8, pipelined=True),

        OpDesc(opClass="SimdUnitStrideLoad",               opLat=6, pipelined=True),
        OpDesc(opClass="SimdStridedStore",                 opLat=4, pipelined=True),
        OpDesc(opClass="SimdIndexedStore",                 opLat=6, pipelined=True),
        OpDesc(opClass="SimdUnitStrideMaskStore",          opLat=6, pipelined=True),
        OpDesc(opClass="SimdUnitStrideSegmentedLoad",      opLat=4, pipelined=True),
        OpDesc(opClass="SimdUnitStrideSegmentedStore",     opLat=4, pipelined=True),
        OpDesc(opClass="SimdWholeRegisterStore",           opLat=6, pipelined=True),
    ]
    count = 1

class CPU_FUPool(FUPool):
    FUList = [
        # Scalar
        Int_ALU(),
        Int_Mult_Unit(),
        Int_Div_Unit(),
        FP_ALU_Unit(),
        FP_Mult_Unit(),
        FP_Div_Unit(),
        LSU(),
        # RVV
        RVV_Int_ALU(),
        RVV_Int_Mult_Unit(),
        RVV_Int_Div_Unit(),
        RVV_Misc_Unit(),
        RVV_FP_ALU(),
        RVV_FP_Mult_Unit(),
        RVV_FP_Div_Unit(),
        RVV_LSU()
    ]

system.cpu.fuPool = CPU_FUPool()

# Run SE mode
root = Root(full_system=False, system=system)
m5.instantiate()
print("Running " + bin)
print("Beginning simulation!")
exit_event = m5.simulate()
print("Exiting")
