#pragma once

#include "Astat/Astat.h"

namespace Astat
{
	namespace Networking
	{
		namespace Http
		{
			class HttpError
			{
			public:
				static int GetBadRequest (std::string& o_message);
				static int GetUnauthorized (std::string& o_message);
				static int GetPaymentRequired (std::string &o_message);
				static int GetForbidden (std::string &o_message);
				static int GetNotFound (std::string &o_message);
				static int GetMethodNotAllowed (std::string &o_message);
				static int GetNotAcceptable (std::string &o_message);
				static int GetProxyAuthenticationRequired (std::string &o_message);
				static int GetRequestTimeout (std::string &o_message);
				static int GetConflict (std::string &o_message);
				static int GetGone (std::string &o_message);
				static int GetLengthRequired (std::string &o_message);
				static int GetPreconditionFailed (std::string &o_message);
				static int GetPayloadTooLarge (std::string &o_message);
				static int GetURITooLong (std::string &o_message);
				static int GetUnsupportedMediaType (std::string &o_message);
				static int GetRangeNotSatisfiable (std::string &o_message);
				static int GetExpectationFailed (std::string &o_message);
				static int GetImATeapot (std::string &o_message);
				static int GetMisdirectedRequest (std::string &o_message);
				static int GetUnprocessableEntity (std::string &o_message);
				static int GetLocked (std::string &o_message);
				static int GetFailedDependency (std::string &o_message);
				static int GetTooEarly (std::string &o_message);
				static int GetUpgradeRequired (std::string &o_message);
				static int GetPreconditionRequired (std::string &o_message);
				static int GetTooManyRequests (std::string &o_message);
				static int GetRequestHeaderFieldsTooLarge (std::string &o_message);
				static int GetUnavailableForLegalReasons (std::string &o_message);

				static int GetInternalServerError (std::string &o_message);
				static int GetNotImplemented (std::string &o_message);
				static int GetBadGateway (std::string &o_message);
				static int GetServiceUnavailable (std::string &o_message);
				static int GetGatewayTimeout (std::string &o_message);
				static int GetHTTPVersionNotSupported (std::string &o_message);
				static int GetVariantAlsoNegotiates (std::string &o_message);
				static int GetInsufficientStorage (std::string &o_message);
				static int GetLoopDetected (std::string &o_message);
				static int GetNotExtended (std::string &o_message);
				static int GetNetworkAuthenticationRequired (std::string &o_message);
			};
		}
	}
}