#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/ServiceBinding.h>
#include <Protocol/Dns4.h>
#include <Protocol/Http.h>

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

void status2print4(EFI_STATUS status)
{
	switch ((int)status)
	{
	case (int)0:
		Print(L"EFI_SUCCESS\nThe operation completed successfully.\n");
		break;
	case (int)1:
		Print(L"EFI_LOAD_ERROR\nThe image failed to load.\n");
		break;
	case (int)2:
		Print(L"EFI_INVALID_PARAMETER\nThe parameter was incorrect.\n");
		break;
	case (int)3:
		Print(L"EFI_UNSUPPORTED\nThe operation is not supported.\n");
		break;
	case (int)4:
		Print(L"EFI_BAD_BUFFER_SIZE\nThe buffer was not the proper size for the request.\n");
		break;
	case (int)5:
		Print(L"EFI_BUFFER_TOO_SMALL\nThe buffer was not large enough to hold the requested data.\n\
The required buffer size is returned in the appropriate\nparameter when this error occurs.\n");
		break;
	case (int)6:
		Print(L"EFI_NOT_READY\nThere is no data pending upon return.\n");
		break;
	case (int)7:
		Print(L"EFI_DEVICE_ERROR\nThe physical device reported an error while attempting the\noperation.\n");
		break;
	case (int)8:
		Print(L"EFI_WRITE_PROTECTED\nThe device can not be written to.\n");
		break;
	case (int)9:
		Print(L"EFI_OUT_OF_RESOURCES\nThe resource has run out.\n");
		break;
	case (int)10:
		Print(L"EFI_VOLUME_CORRUPTED\nAn inconsistency was detected on the file system causing the\noperation to fail.\n");
		break;
	case (int)11:
		Print(L"EFI_VOLUME_FULL\nThere is no more space on the file system.\n");
		break;
	case (int)12:
		Print(L"EFI_NO_MEDIA\nThe device does not contain any medium to perform the\noperation.\n");
		break;
	case (int)13:
		Print(L"EFI_MEDIA_CHANGED\nThe medium in the device has changed since the last\naccess.\n");
		break;
	case (int)14:
		Print(L"EFI_NOT_FOUND\nThe item was not found.\n");
		break;
	case (int)15:
		Print(L"EFI_ACCESS_DENIED\nAccess was denied.\n");
		break;
	case (int)16:
		Print(L"EFI_NO_RESPONSE\nThe server was not found or did not respond to the request.\n");
		break;
	case (int)17:
		Print(L"EFI_NO_MAPPING\nA mapping to the device does not exist.\n");
		break;
	case (int)18:
		Print(L"EFI_TIMEOUT\nA timeout time expired.\n");
		break;
	case (int)19:
		Print(L"EFI_NOT_STARTED\nThe protocol has not been started.\n");
		break;
	case (int)20:
		Print(L"EFI_ALREADY_STARTED\nThe protocol has already been started.\n");
		break;
	case (int)21:
		Print(L"EFI_ABORTED\nThe operation was aborted.\n");
		break;
	case (int)22:
		Print(L"EFI_ICMP_ERROR\nAn ICMP error occurred during the network operation.\n");
		break;
	case (int)23:
		Print(L"EFI_TFTP_ERROR\nA TFTP error occurred during the network operation.\n");
		break;
	case (int)24:
		Print(L"EFI_PROTOCOL_ERROR\nA protocol error occurred during the network operation.\n");
		break;
	case (int)25:
		Print(L"EFI_INCOMPATIBLE_VERSION\nA function encountered an internal version that was\n\
incompatible with a version requested by the caller.\n");
		break;
	case (int)26:
		Print(L"EFI_SECURITY_VIOLATION\nThe function was not performed due to a security violation.\n");
		break;
	case (int)27:
		Print(L"EFI_CRC_ERROR\nA CRC error was detected.\n");
		break;
	case (int)28:
		Print(L"EFI_END_OF_MEDIA\nThe beginning or end of media was reached.\n");
		break;
	case (int)31:
		Print(L"EFI_END_OF_FILE\nThe end of the file was reached.\n");
		break;
	case (int)32:
		Print(L"EFI_INVALID_LANGUAGE\nThe language specified was invalid.\n");
		break;
	case (int)33:
		Print(L"EFI_COMPROMISED_DATA\nThe security\nstatus of the data is unknown or compromised\n\
and the data must be updated or replaced to restore a valid\nsecurity status.\n");
		break;
	case (int)35:
		Print(L"EFI_HTTP_ERROR\nA HTTP error occurred during the network operation.\n");
		break;
	default:
		Print(L"default: %u\n", (int)status);
		break;
	}
	Print(L"status: %u\n", (int)status);
}

EFI_STATUS edk2dns(IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE* SystemTable)
{

	UINTN HandleCount;
	EFI_HANDLE* HandleBuffer;
	gBS->LocateHandleBuffer(ByProtocol,
		&gEfiDns4ServiceBindingProtocolGuid, NULL,
		&HandleCount, &HandleBuffer);
	UINTN Index;
	EFI_STATUS Status;
	Print(L"Found: %d with dns guid\n", HandleCount);
	EFI_SERVICE_BINDING_PROTOCOL* esbp;
	for (Index = 0; Index < HandleCount; Index++)
	{
		Print(L"Handle: %d dns guid\n", Index);
		Status = gBS->OpenProtocol(
			HandleBuffer[Index],
			&gEfiDns4ServiceBindingProtocolGuid,
			(VOID**)&esbp,
			gImageHandle,   //For UEFI applications, this is 
							//the image handle of 
							//the UEFI application that is 
							//opening the protocol 
							//interface. 186 page
			NULL,
			EFI_OPEN_PROTOCOL_GET_PROTOCOL);
		if (EFI_ERROR(Status))
		{
			Print(L"Error OpenProtocol %d\n", Status);
			status2print4(Status);
			return Status;
		}
		else
		{
			Print(L"No error OpenProtocol\n");
			EFI_HANDLE DnsHandle = NULL;
			Status = esbp->CreateChild(esbp, &DnsHandle);
			if (EFI_ERROR(Status))
			{
				Print(L"Error CreateChild %d\n", Status);
				status2print4(Status);

				//create chlid docs 390
				if (DnsHandle == NULL)
				{
					Print(L"DnsHandle null\n");
				}
				else
				{
					Print(L"DnsHandle not null\n");
				}
				return Status;
			}
			else
			{
				EFI_DNS4_PROTOCOL* efi_dns4_protocol;
				Print(L"No error CreateChild\n");
				Status = gBS->HandleProtocol(DnsHandle,
					&gEfiDns4ProtocolGuid, (VOID**)&efi_dns4_protocol);
				if (EFI_ERROR(Status))
				{
					Print(L"Error HandleProtocol %d\n", Status);
					status2print4(Status);
					return Status;
				}
				else
				{
					Print(L"No error HandleProtocol\n");
					EFI_DNS4_CONFIG_DATA efi_dns4_config_data;
					efi_dns4_config_data.UseDefaultSetting = TRUE;
					// defined on 1513
					efi_dns4_config_data.DnsServerListCount = 0;// 1;
					efi_dns4_config_data.DnsServerList = NULL;
					efi_dns4_config_data.EnableDnsCache = FALSE;
					efi_dns4_config_data.Protocol = 17;
					efi_dns4_config_data.LocalPort = 0;
					efi_dns4_config_data.RetryCount = 12;
					efi_dns4_config_data.RetryInterval = 5;
					Status = efi_dns4_protocol->Configure(
						efi_dns4_protocol, &efi_dns4_config_data);
					if (EFI_ERROR(Status))
					{
						Print(L"Error Configure %d\n", Status);
						status2print4(Status);
						return Status;
					}
					else
					{
						Print(L"No error Configure\n");

						EFI_DNS4_COMPLETION_TOKEN efi_dns4_completion_token;
						EFI_EVENT efi_event_for_wait;

						Status = gBS->CreateEvent(EVT_TIMER, TPL_NOTIFY, NULL, NULL, &efi_event_for_wait);
						if (EFI_ERROR(Status))
						{
							Print(L"Error EFI_CREATE_EVENT efi_event_for_wait %d\n", Status);
							status2print4(Status);
							return Status;
						}
						else
						{
							Print(L"No Error EFI_CREATE_EVENT efi_event_for_wait %d\n", Status);
							efi_dns4_completion_token.Event = efi_event_for_wait;
							Status = efi_dns4_protocol->HostNameToIp(efi_dns4_protocol, L"www.google.com", &efi_dns4_completion_token);
							if (EFI_ERROR(Status))
							{
								Print(L"Error HostNameToIp %d\n", Status);
								status2print4(Status);
								return Status;
							}
							else
							{
								UINTN event_index;

								Status = gBS->WaitForEvent(1, &efi_event_for_wait, &event_index);
								if (EFI_ERROR(Status))
								{
									Print(L"Error efi_wait_for_event %d\n", Status);
									status2print4(Status);
									return Status;
								}
								else
								{
									Print(L"No Error efi_wait_for_event\n");
								}
								Status = gBS->CloseEvent(efi_event_for_wait);
								if (EFI_ERROR(Status))
								{
									Print(L"Error CloseEvent %d\n", Status);
									status2print4(Status);
									return Status;
								}
								else
								{
									Print(L"No Error CloseEvent\n");
								}
								Print(L"efi_dns4_completion_token status %d\n", efi_dns4_completion_token.Status);
								status2print4(efi_dns4_completion_token.Status);

								Print(L"IpCount: %d\n", efi_dns4_completion_token.RspData.H2AData->IpCount);

								UINTN Index2;
								for (Index2 = 0; Index2 < efi_dns4_completion_token.RspData.H2AData->IpCount; ++Index2)
								{
									Print(L"Ip: %d.%d.%d.%d\n",
										efi_dns4_completion_token.
										RspData.H2AData->IpList[Index2].
										Addr[0],
										efi_dns4_completion_token.
										RspData.H2AData->IpList[Index2].
										Addr[1],
										efi_dns4_completion_token.
										RspData.H2AData->IpList[Index2].
										Addr[2],
										efi_dns4_completion_token.
										RspData.H2AData->IpList[Index2].
										Addr[3]);
								}
							}
						}
					}
				}
				esbp->DestroyChild(esbp, DnsHandle);
			}
		}
	}
	//
	// Free the array of handles allocated by gBS->LocateHandleBuffer()
	//
	FreePool(HandleBuffer);
	return EFI_SUCCESS;
}
