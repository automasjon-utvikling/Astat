#include "atpch.h"

#include "HttpError.h"

int Astat::Networking::Http::HttpError::GetBadRequest (std::string &o_message)
{
	return 400;
}

int Astat::Networking::Http::HttpError::GetUnauthorized (std::string &o_message)
{
	return 401;
}

int Astat::Networking::Http::HttpError::GetPaymentRequired (std::string &o_message)
{
	return 402;
}

int Astat::Networking::Http::HttpError::GetForbidden (std::string &o_message)
{
	return 403;
}

int Astat::Networking::Http::HttpError::GetNotFound (std::string &o_message)
{
	o_message = "Not Found";
	return 404;
}

int Astat::Networking::Http::HttpError::GetMethodNotAllowed (std::string &o_message)
{
	return 405;
}

int Astat::Networking::Http::HttpError::GetNotAcceptable (std::string &o_message)
{
	return 406;
}

int Astat::Networking::Http::HttpError::GetProxyAuthenticationRequired (std::string &o_message)
{
	return 407;
}

int Astat::Networking::Http::HttpError::GetRequestTimeout (std::string &o_message)
{
	return 408;
}

int Astat::Networking::Http::HttpError::GetConflict (std::string &o_message)
{
	return 409;
}

int Astat::Networking::Http::HttpError::GetGone (std::string &o_message)
{
	return 410;
}

int Astat::Networking::Http::HttpError::GetLengthRequired (std::string &o_message)
{
	return 411;
}

int Astat::Networking::Http::HttpError::GetPreconditionFailed (std::string &o_message)
{
	return 412;
}

int Astat::Networking::Http::HttpError::GetPayloadTooLarge (std::string &o_message)
{
	return 413;
}

int Astat::Networking::Http::HttpError::GetURITooLong (std::string &o_message)
{
	return 414;
}

int Astat::Networking::Http::HttpError::GetUnsupportedMediaType (std::string &o_message)
{
	return 415;
}

int Astat::Networking::Http::HttpError::GetRangeNotSatisfiable (std::string &o_message)
{
	return 416;
}

int Astat::Networking::Http::HttpError::GetExpectationFailed (std::string &o_message)
{
	return 417;
}

int Astat::Networking::Http::HttpError::GetImATeapot (std::string &o_message)
{
	return 418;
}

int Astat::Networking::Http::HttpError::GetMisdirectedRequest (std::string &o_message)
{
	return 421;
}

int Astat::Networking::Http::HttpError::GetUnprocessableEntity (std::string &o_message)
{
	return 422;
}

int Astat::Networking::Http::HttpError::GetLocked (std::string &o_message)
{
	return 423;
}

int Astat::Networking::Http::HttpError::GetFailedDependency (std::string &o_message)
{
	return 424;
}

int Astat::Networking::Http::HttpError::GetTooEarly (std::string &o_message)
{
	return 425;
}

int Astat::Networking::Http::HttpError::GetUpgradeRequired (std::string &o_message)
{
	return 426;
}

int Astat::Networking::Http::HttpError::GetPreconditionRequired (std::string &o_message)
{
	return 428;
}

int Astat::Networking::Http::HttpError::GetTooManyRequests (std::string &o_message)
{
	return 429;
}

int Astat::Networking::Http::HttpError::GetRequestHeaderFieldsTooLarge (std::string &o_message)
{
	return 431;
}

int Astat::Networking::Http::HttpError::GetUnavailableForLegalReasons (std::string &o_message)
{
	return 451;
}

int Astat::Networking::Http::HttpError::GetInternalServerError (std::string &o_message)
{
	return 500;
}

int Astat::Networking::Http::HttpError::GetNotImplemented (std::string &o_message)
{
	return 501;
}

int Astat::Networking::Http::HttpError::GetBadGateway (std::string &o_message)
{
	return 502;
}

int Astat::Networking::Http::HttpError::GetServiceUnavailable (std::string &o_message)
{
	return 503;
}

int Astat::Networking::Http::HttpError::GetGatewayTimeout (std::string &o_message)
{
	return 504;
}

int Astat::Networking::Http::HttpError::GetHTTPVersionNotSupported (std::string &o_message)
{
	return 505;
}

int Astat::Networking::Http::HttpError::GetVariantAlsoNegotiates (std::string &o_message)
{
	return 506;
}

int Astat::Networking::Http::HttpError::GetInsufficientStorage (std::string &o_message)
{
	return 507;
}

int Astat::Networking::Http::HttpError::GetLoopDetected (std::string &o_message)
{
	return 508;
}

int Astat::Networking::Http::HttpError::GetNotExtended (std::string &o_message)
{
	return 510;
}

int Astat::Networking::Http::HttpError::GetNetworkAuthenticationRequired (std::string &o_message)
{
	return 511;
}
