#include "pch.h"
#include "global_struct.h"
#include "FaceAuthenticatorException.h"
#include "ServerApiException.h"
#include "PolicyApi.h"
#include "UserApi.h"
#include "FaceAuthenticator.h"

const std::wstring FaceAuthenticator::CameraName = L"Camera Name"; // Example value
const std::wstring FaceAuthenticator::Channel = L"Channel";

FaceAuthenticator::FaceAuthenticator(RequestInfo a_serverInfo) 
	: serverInfo(a_serverInfo)
{
}

void FaceAuthenticator::PrepareAuthentication(const std::wstring& ssoId)
{
	AuthListResponse authListResponse;
	PolicyApi policyApi(this->serverInfo);
	
	if (!policyApi.GetAuthenticationList(L"-1", ssoId, authListResponse))
	{
		throw ServerApiException(ServerApiError::NetworkCommunicationFailed);
	}

	if (authListResponse.resultCode != L"0200.000")
	{
		std::wstring message = L"";
		if (!authListResponse.resultMessage.empty())
		{
			message = authListResponse.resultMessage;
		}
		throw new FaceAuthenticatorException(message);
	}

	this->cachedPrepareAuthResultData = authListResponse.apcToken;

	UserInfoResponse userInfoResponse;
	UserApi userApi(this->serverInfo);
	if (!userApi.GetUserInfo(ssoId, authListResponse.apcToken, userInfoResponse))
	{
		throw ServerApiException(ServerApiError::NetworkCommunicationFailed);
	}

	if (userInfoResponse.resultCode != L"0200.000")
	{
		std::wstring message = L"";
		if (!userInfoResponse.resultMessage.empty())
		{
			message = userInfoResponse.resultMessage;
		}
		throw FaceAuthenticatorException(message);
	}

	this->isFaceRegistration = userInfoResponse.registeredFace;
	this->isPasswordRegistration = userInfoResponse.pwValue;
}

void FaceAuthenticator::Authenticate(const std::wstring& ssoId, std::wstring& validUntilDate, std::wstring& secureToken, std::wstring& password)
{
	if (this->cachedtAuthCapturedData.empty())
	{
		MKAuthenticator mkAuthenticator(this->CameraName);
		mkAuthenticator.TopMost = true;

		if (!mkAuthenticator.IsCamOpened())
		{
			throw FaceAuthenticatorException(FaceAuthError::InitDeviceFailed);
		}

		if (!mkAuthenticator.StartCapture(this->CaptureWaitingTime))
		{
			throw FaceAuthenticatorException(FaceAuthError::StartCaptureFailed);
		}

		this->cachedtAuthCapturedData = mkAuthenticator.Authentication(ssoId, this->Channel, SysInfo::SysInfo::GetMacAddress());
		if (this->cachedtAuthCapturedData.empty())
		{
			throw FaceAuthenticatorException(FaceAuthError::CaptureFailed);
		}

		if (mkAuthenticator.IsCamOpened())
		{
			mkAuthenticator.ReleaseCam();
		}
	}

	FaceApi faceApi(this->serverInfo);
	FaceAuthResponse faceAuthResponse;

	FaceAuthRequestDto faceAuthRequestDto;
	faceAuthRequestDto.userId = ssoId;
	faceAuthRequestDto.data = this->cachedtAuthCapturedData;

	if (!faceApi.Authentication(faceAuthRequestDto, this->cachedPrepareAuthResultData, faceAuthResponse))
	{
		throw ServerApiException(ServerApiError::NetworkCommunicationFailed);
	}

	if (faceAuthResponse.resultCode != L"0200.000")
	{
		std::wstring message = L"";
		if (!faceAuthResponse.resultMessage.empty())
		{
			message = faceAuthResponse.resultMessage;
		}

		if (!faceAuthResponse.code.empty())
		{
			message += L"(에러코드 : " + faceAuthResponse.code + L")";
		}

		throw FaceAuthenticatorException(message);
	}

	validUntilDate = faceAuthResponse.validUntilDate;
	secureToken = faceAuthResponse.secureToken;
	password = faceAuthResponse.password;
}

void FaceAuthenticator::Register(const std::wstring& ssoId, const std::wstring& ssoPw)
{
	if (this->cachedRegisterCapturedData.empty())
	{
		MKRegister mkRegister(this->CameraName);
		mkRegister.TopMost = true;

		if (!mkRegister.IsCamOpened())
		{
			throw FaceAuthenticatorException(FaceAuthError::InitDeviceFailed);
		}

		if (!mkRegister.StartCapture(this->CaptureWaitingTime))
		{
			throw FaceAuthenticatorException(FaceAuthError::StartCaptureFailed);
		}

		this->cachedtAuthCapturedData = mkRegister.Registration(ssoId, this->Channel, ssoPw, SysInfo::SysInfo::GetMacAddress());
		if (this->cachedRegisterCapturedData.empty())
		{
			throw FaceAuthenticatorException(FaceAuthError::CaptureFailed);
		}

		if (mkRegister.IsCamOpened())
		{
			mkRegister.ReleaseCam();
		}
	}

	if (this->cachedPrepareAuthResultData.empty())
	{
		this->PrepareAuthentication(ssoId);
	}

	FaceApi faceApi(this->serverInfo);
	FaceAuthResponse faceRegisterResponse;

	FaceRegisterRequestDto faceRegisterRequestDto;
	faceRegisterRequestDto.userId = ssoId;
	faceRegisterRequestDto.data = this->cachedRegisterCapturedData;
	faceRegisterRequestDto.password = ssoPw;

	if (!faceApi.Register(faceRegisterRequestDto, this->cachedPrepareAuthResultData, faceRegisterResponse)) {
		throw ServerApiException(ServerApiError::NetworkCommunicationFailed);
	}

	if (faceRegisterResponse.resultCode != L"0200.000")
	{
		std::wstring message = L"";
		if (!faceRegisterResponse.resultMessage.empty())
		{
			message = faceRegisterResponse.resultMessage;
		}

		if (!faceRegisterResponse.code.empty())
		{
			message += L"(에러코드 : " + faceRegisterResponse.code + L")";
		}
		throw FaceAuthenticatorException(message);
	}
}

bool FaceAuthenticator::CheckRegistered(const std::wstring& ssoId)
{
	if (this->cachedtAuthCapturedData.empty())
	{
		MKAuthenticator mkAuthenticator(this->CameraName);
		mkAuthenticator.TopMost = true;

		if (!mkAuthenticator.IsCamOpened()) 
		{
			throw FaceAuthenticatorException(FaceAuthError::InitDeviceFailed);
		}

		if (!mkAuthenticator.StartCapture(this->CaptureWaitingTime))
		{
			throw FaceAuthenticatorException(FaceAuthError::StartCaptureFailed);
		}

		this->cachedtAuthCapturedData = mkAuthenticator.Authentication(ssoId, this->Channel, SysInfo::SysInfo::GetMacAddress());
		if (this->cachedtAuthCapturedData.empty())
		{
			throw FaceAuthenticatorException(FaceAuthError::CaptureFailed);
		}

		if (mkAuthenticator.IsCamOpened())
		{
			mkAuthenticator.ReleaseCam();
		}
	}

	if (this->cachedPrepareAuthResultData.empty())
	{
		this->PrepareAuthentication(ssoId);
	}

	FaceApi faceApi(this->serverInfo);
	FaceGetStatusResponse faceGetStatusResponse;
	FaceGetStatusRequestDto faceGetStatusRequestDto;
	faceGetStatusRequestDto.userId = ssoId;
	faceGetStatusRequestDto.data = this->cachedtAuthCapturedData;

	if (!faceApi.GetStatus(faceGetStatusRequestDto, this->cachedPrepareAuthResultData, faceGetStatusResponse)) {
		throw ServerApiException(ServerApiError::NetworkCommunicationFailed);
	}

	if (faceGetStatusResponse.resultCode != L"0200.000")
	{
		std::wstring message = L"";
		if (faceGetStatusResponse.resultMessage.empty())
		{
			message = faceGetStatusResponse.resultMessage;
		}

		throw FaceAuthenticatorException(message);
	}

	return faceGetStatusResponse.isRegistered;
}

void FaceAuthenticator::MotpAuthentication(const std::wstring& ssoId, const std::wstring& otpNumber, std::wstring& encPassword)
{
	MotpApi motpApi(this->serverInfo);
	MotpAuthResponse motpAuthResponse;

	// MTOP 인증
	MotpAuthRequestDto motpAuthenticationRequest;
	motpAuthenticationRequest.userId = ssoId;
	motpAuthenticationRequest.otpNumber = otpNumber;

	// 결과 값 처리 필요
	if (!motpApi.Authentication(this->cachedPrepareAuthResultData, motpAuthenticationRequest, motpAuthResponse))
	{
		throw ServerApiException(ServerApiError::NetworkCommunicationFailed);
	}
	if (motpAuthResponse.resultCode != L"0200.000")
	{
		std::wstring message = L"";
		if (!motpAuthResponse.resultMessage.empty())
		{
			message = motpAuthResponse.resultMessage;
		}
		throw new FaceAuthenticatorException(message);
	}
	if (motpAuthResponse.password.empty())
	{
		throw ServerApiException(ServerApiError::InvalidResponseDataValue);
	}

	encPassword = motpAuthResponse.password;
}

void FaceAuthenticator::ClearCachedData()
{
	this->cachedtAuthCapturedData = L"";
	this->cachedRegisterCapturedData = L"";
	this->cachedPrepareAuthResultData = L"";
}
