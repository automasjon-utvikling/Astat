#include "atpch.h"

#include "Tls10.h"

namespace Astat
{
	namespace Networking
	{
		namespace Tls10
		{
			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// An inappropriate message was received. This alert is always fatal
			/// and should never be observed in communication between proper
			/// implementations.
			struct Alert unexpected_message = { AlertLevel::fatal, AlertDescription::unexpected_message };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// This alert is returned if a record is received with an incorrect
			/// MAC.This message is always fatal.
			struct Alert bad_record_mac = { AlertLevel::fatal, AlertDescription::bad_record_mac };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A TLSCiphertext decrypted in an invalid way: either it wasn`t an
			/// even multiple of the block length or its padding values, when
			///checked, weren`t correct.This message is always fatal.
			struct Alert decryption_failed = { AlertLevel::fatal, AlertDescription::decryption_failed };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A TLSCiphertext record was received which had a length more than
			/// 2 ^ 14 + 2048 bytes, or a record decrypted to a TLSCompressed record
			/// with more than 2 ^ 14 + 1024 bytes.This message is always fatal.
			struct Alert record_overflow = { AlertLevel::fatal, AlertDescription::record_overflow };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// The decompression function received improper input (e.g. data
			/// that would expand to excessive length).This message is always
			/// fatal.
			struct Alert decompression_failure = { AlertLevel::fatal, AlertDescription::decompression_failure };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// Reception of a handshake_failure alert message indicates that the
			/// sender was unable to negotiate an acceptable set of security
			/// parameters given the options available.This is a fatal error.
			struct Alert handshake_failure = { AlertLevel::fatal, AlertDescription::handshake_failure };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A certificate was corrupt, contained signatures that did not
			/// verify correctly, etc.
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert bad_certificate_fatal = { AlertLevel::fatal, AlertDescription::bad_certificate };
			struct Alert bad_certificate_warning = { AlertLevel::warning, AlertDescription::bad_certificate };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A certificate was of an unsupported type.
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert unsupported_certificate_fatal = { AlertLevel::fatal, AlertDescription::unsupported_certificate };
			struct Alert unsupported_certificate_warning = { AlertLevel::warning, AlertDescription::unsupported_certificate };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A certificate was revoked by its signer.
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert certificate_revoked_fatal = { AlertLevel::fatal, AlertDescription::certificate_revoked };
			struct Alert certificate_revoked_warning = { AlertLevel::warning, AlertDescription::certificate_revoked };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A certificate has expired or is not currently valid.
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert certificate_expired_fatal = { AlertLevel::fatal, AlertDescription::certificate_expired };
			struct Alert certificate_expired_warning = { AlertLevel::warning, AlertDescription::certificate_expired };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// Some other (unspecified) issue arose in processing the
			/// certificate, rendering it unacceptable.
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert certificate_unknown_fatal = { AlertLevel::fatal, AlertDescription::certificate_unknown };
			struct Alert certificate_unknown_warning = { AlertLevel::warning, AlertDescription::certificate_unknown };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A field in the handshake was out of range or inconsistent with
			/// other fields.This is always fatal.
			struct Alert illegal_parameter = { AlertLevel::fatal, AlertDescription::illegal_parameter };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A valid certificate chain or partial chain was received, but the
			/// certificate was not accepted because the CA certificate could not
			/// be located or couldn`t be matched with a known, trusted CA.This
			/// message is always fatal.
			struct Alert unknown_ca = { AlertLevel::fatal, AlertDescription::unknown_ca };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A valid certificate was received, but when access control was
			/// applied, the sender decided not to proceed with negotiation.
			/// This message is always fatal.
			struct Alert access_denied = { AlertLevel::fatal, AlertDescription::access_denied };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A message could not be decoded because some field was out of the
			/// specified range or the length of the message was incorrect.This
			/// message is always fatal.
			struct Alert decode_error = { AlertLevel::fatal, AlertDescription::decode_error };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A handshake cryptographic operation failed, including being
			/// unable to correctly verify a signature, decrypt a key exchange,
			/// or validate a finished message.
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert decrypt_error_fatal = { AlertLevel::fatal, AlertDescription::decrypt_error };
			struct Alert decrypt_error_warning = { AlertLevel::warning, AlertDescription::decrypt_error };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// A negotiation not in compliance with export restrictions was
			/// detected; for example, attempting to transfer a 1024 bit
			/// ephemeral RSA key for the RSA_EXPORT handshake method.This
			/// message is always fatal.
			struct Alert export_restriction = { AlertLevel::fatal, AlertDescription::export_restriction };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// The protocol version the client has attempted to negotiate is
			/// recognized, but not supported. (For example, old protocol
			/// versions might be avoided for security reasons).This message is
			/// always fatal.
			struct Alert protocol_version = { AlertLevel::fatal, AlertDescription::protocol_version };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// Returned instead of handshake_failure when a negotiation has
			/// failed specifically because the server requires ciphers more
			/// secure than those supported by the client.This message is always
			/// fatal.
			struct Alert insufficient_security = { AlertLevel::fatal, AlertDescription::insufficient_security };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// An internal error unrelated to the peer or the correctness of the
			/// protocol makes it impossible to continue (such as a memory
			/// allocation failure).This message is always fatal.
			struct Alert internal_error = { AlertLevel::fatal, AlertDescription::internal_error };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// This handshake is being canceled for some reason unrelated to a
			/// protocol failure.If the user cancels an operation after the
			/// handshake is complete, just closing the connection by sending a
			/// close_notify is more appropriate.This alert should be followed
			/// by a close_notify.This message is generally a warning. 
			/// The sending party may determine at its discretion whether this is a fatal
			/// error or not; if an alert with a level of warning is received, the
			/// receiving party may decide at its discretion whether to treat this as
			/// a fatal error or not.
			struct Alert user_canceled_fatal = { AlertLevel::fatal, AlertDescription::user_canceled };
			struct Alert user_canceled_warning = { AlertLevel::warning, AlertDescription::user_canceled };

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2.2
			/// Sent by the client in response to a hello request or by the
			/// server in response to a client hello after initial handshaking.
			/// Either of these would normally lead to renegotiation; when that
			/// is not appropriate, the recipient should respond with this alert;
			/// at that point, the original requester can decide whether to
			/// proceed with the connection.One case where this would be
			/// appropriate would be where a server has spawned a process to
			/// satisfy a request; the process might receive security parameters
			/// (key length, authentication, etc.) at startup andit might be
			/// difficult to communicate changes to these parameters after that
			/// point.This message is always a warning.
			struct Alert no_renegotiation = { AlertLevel::warning, AlertDescription::no_renegotiation };
		}
	}
}