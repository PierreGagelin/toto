[Defines]
    PLATFORM_NAME = TotoPkg
    PLATFORM_GUID = FB2E2496-0A00-4103-8BA1-EC71344D654E
    PLATFORM_VERSION = 0.1
    DSC_SPECIFICATION = 0x00010005
    OUTPUT_DIRECTORY = Build/TotoPkg
    SUPPORTED_ARCHITECTURES = IA32|X64
    BUILD_TARGETS = DEBUG|RELEASE
    SKUID_IDENTIFIER = DEFAULT

[LibraryClasses]
    BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
    BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
    DebugLib|MdePkg/Library/UefiDebugLibStdErr/UefiDebugLibStdErr.inf
    DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
    DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
    MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
    PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
    PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
    UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
    UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
    UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
    UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf

    Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
    Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibTcg2/Tpm2DeviceLibTcg2.inf

[Components]
    TotoPkg/toto.inf
