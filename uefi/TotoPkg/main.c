// EDKII headers
#include <Library/Tpm2CommandLib.h>
#include <Library/Tpm2DeviceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Uefi.h>

///
/// @brief UEFI entry point
///
EFI_STATUS EFIAPI UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    TPML_ALG_PROPERTY alg_list;
    EFI_STATUS status;

    status = Tpm2RequestUseTpm();
    AsciiPrint("Requested TPM usage uefi_status=%r\n", status);

    // Start TPM up
    status = Tpm2Startup(TPM_SU_STATE);
    AsciiPrint("Started TPM up uefi_status=%r\n", status);

    // Run TPM full self test
    status = Tpm2SelfTest(YES);
    AsciiPrint("Ran TPM self test uefi_status=%r\n", status);

    // Print supported algorithms
    status = Tpm2GetCapabilitySupportedAlg(&alg_list);
    AsciiPrint("Got TPM supported algorithms uefi_status=%r\n", status);
    if (EFI_ERROR(status)) {
        goto end;
    }
    for (UINT32 i = 0; i < alg_list.count ; ++i) {
        AsciiPrint("TPM algorithm index=%u algorithm=%u\n", i, alg_list.algProperties[i].alg);
    }

end:
    // Wait 10 seconds before end of program
    gBS->Stall(10 * 1000 * 1000);

    return status;
}
