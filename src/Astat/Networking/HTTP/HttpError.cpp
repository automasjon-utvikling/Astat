#include "atpch.h"

#include "HttpError.h"

int Astat::Networking::Http::HttpError::GetBadRequest (std::string &o_message)
{
	o_message = "Bad Request";
	return 400;
} // GetBadRequest()

int Astat::Networking::Http::HttpError::GetUnauthorized (std::string &o_message)
{
	o_message = "Unauthorized";
	return 401;
} // GetUnauthorized()

int Astat::Networking::Http::HttpError::GetPaymentRequired (std::string &o_message)
{
	o_message = "Payment Required";
	return 402;
} // GetPaymentRequired()

int Astat::Networking::Http::HttpError::GetForbidden (std::string &o_message)
{
	o_message = "Forbidden";
	return 403;
} // GetForbidden()

int Astat::Networking::Http::HttpError::GetNotFound (std::string &o_message)
{
	o_message = "Not Found";
	return 404;
} // GetNotFound()

int Astat::Networking::Http::HttpError::GetMethodNotAllowed (std::string &o_message)
{
	o_message = "Method Not Allowed";
	return 405;
} // GetMethodNotAllowed()

int Astat::Networking::Http::HttpError::GetNotAcceptable (std::string &o_message)
{
	o_message = "Not Acceptable";
	return 406;
} // GetNotAcceptable()

int Astat::Networking::Http::HttpError::GetProxyAuthenticationRequired (std::string &o_message)
{
	o_message = "Proxy Authentication Required";
	return 407;
} // GetProxyAuthenticationRequired()

int Astat::Networking::Http::HttpError::GetRequestTimeout (std::string &o_message)
{
	o_message = "Request Timeout";
	return 408;
} // GetRequestTimeout()

int Astat::Networking::Http::HttpError::GetConflict (std::string &o_message)
{
	o_message = "Conflict";
	return 409;
} // GetConflict()

int Astat::Networking::Http::HttpError::GetGone (std::string &o_message)
{
	o_message = "Gone";
	return 410;
} // GetGone()

int Astat::Networking::Http::HttpError::GetLengthRequired (std::string &o_message)
{
	o_message = "Length Required";
	return 411;
} // GetLengthRequired()

int Astat::Networking::Http::HttpError::GetPreconditionFailed (std::string &o_message)
{
	o_message = "Precondition Failed";
	return 412;
} // GetPreconditionFailed()

int Astat::Networking::Http::HttpError::GetPayloadTooLarge (std::string &o_message)
{
	o_message = "Payload Too Large";
	return 413;
} // GetPayloadTooLarge()

int Astat::Networking::Http::HttpError::GetURITooLong (std::string &o_message)
{
	o_message = "URI Too Long";
	return 414;
} // GetURITooLong()

int Astat::Networking::Http::HttpError::GetUnsupportedMediaType (std::string &o_message)
{
	o_message = "UnsupportedMediaType";
	return 415;
} // GetUnsupportedMediaType()

int Astat::Networking::Http::HttpError::GetRangeNotSatisfiable (std::string &o_message)
{
	o_message = "Range Not Satisfiable";
	return 416;
} // GetRangeNotSatisfiable

int Astat::Networking::Http::HttpError::GetExpectationFailed (std::string &o_message)
{
	o_message = "Expectation Failed";
	return 417;
} // GetExpectationFailed()

int Astat::Networking::Http::HttpError::GetImATeapot (std::string &o_message)
{
	o_message = "I'm A Teapot";
	return 418;
} // GetImATeapot()

int Astat::Networking::Http::HttpError::GetMisdirectedRequest (std::string &o_message)
{
	o_message = "Misdirected Request";
	return 421;
} // GetMisdirectedRequest()

int Astat::Networking::Http::HttpError::GetUnprocessableEntity (std::string &o_message)
{
	o_message = "Unprocessable Entity";
	return 422;
} // GetUnprocessableEntity()

int Astat::Networking::Http::HttpError::GetLocked (std::string &o_message)
{
	o_message = "Locked";
	return 423;
} // GetLocked()

int Astat::Networking::Http::HttpError::GetFailedDependency (std::string &o_message)
{
	o_message = "Failed Dependency";
	return 424;
} // GetFailedDependency()

int Astat::Networking::Http::HttpError::GetTooEarly (std::string &o_message)
{
	o_message = "Too Early";
	return 425;
} // GetTooEarly()

int Astat::Networking::Http::HttpError::GetUpgradeRequired (std::string &o_message)
{
	o_message = "Upgrade Required";
	return 426;
} // GetUpgradeRequired()

int Astat::Networking::Http::HttpError::GetPreconditionRequired (std::string &o_message)
{
	o_message = "Precondition Required";
	return 428;
} // GetPreconditionRequired()

int Astat::Networking::Http::HttpError::GetTooManyRequests (std::string &o_message)
{
	o_message = "Too Many Requests";
	return 429;
} // GetTooManyRequests()

int Astat::Networking::Http::HttpError::GetRequestHeaderFieldsTooLarge (std::string &o_message)
{
	o_message = "Request Header Fields Too Large";
	return 431;
} // GetRequestHeaderFieldsTooLarge()

int Astat::Networking::Http::HttpError::GetUnavailableForLegalReasons (std::string &o_message)
{
	o_message = "Unavailable For Legal Reasons";
	return 451;
} // GetUnavailableForLegalReasons()

int Astat::Networking::Http::HttpError::GetInternalServerError (std::string &o_message)
{
	o_message = "Internal Server Error";
	return 500;
} // GetInternalServerError()

int Astat::Networking::Http::HttpError::GetNotImplemented (std::string &o_message)
{
	o_message = "Not Implemented";
	return 501;
} // GetNotImplemented()

int Astat::Networking::Http::HttpError::GetBadGateway (std::string &o_message)
{
	o_message = "Bad Gateway";
	return 502;
} // GetBadGateway()

int Astat::Networking::Http::HttpError::GetServiceUnavailable (std::string &o_message)
{
	o_message = "Service Unavailable";
	return 503;
} // GetServiceUnavailable()

int Astat::Networking::Http::HttpError::GetGatewayTimeout (std::string &o_message)
{
	o_message = "Gateway Timeout";
	return 504;
} // GetGatewayTimeout()

int Astat::Networking::Http::HttpError::GetHTTPVersionNotSupported (std::string &o_message)
{
	o_message = "HTTP Version Not Supported";
	return 505;
} // GetHTTPVersionNotSupported()

int Astat::Networking::Http::HttpError::GetVariantAlsoNegotiates (std::string &o_message)
{
	o_message = "Variant Also Negotiates";
	return 506;
} // GetVariantAlsoNegotiates()

int Astat::Networking::Http::HttpError::GetInsufficientStorage (std::string &o_message)
{
	o_message = "Insufficient Storage";
	return 507;
} // GetInsufficientStorage()

int Astat::Networking::Http::HttpError::GetLoopDetected (std::string &o_message)
{
	o_message = "Loop Detected";
	return 508;
} // GetLoopDetected()

int Astat::Networking::Http::HttpError::GetNotExtended (std::string &o_message)
{
	o_message = "Not Extended";
	return 510;
} // GetNotExtended()

int Astat::Networking::Http::HttpError::GetNetworkAuthenticationRequired (std::string &o_message)
{
	o_message = "Network Authentication Required";
	return 511;
} // GetNetworkAuthenticationRequired()
