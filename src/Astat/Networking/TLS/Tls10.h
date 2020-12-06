#pragma once

#include "Astat/Astat.h"

namespace Astat
{
	namespace Networking
	{
		/// @brief https://tools.ietf.org/html/rfc2246
		namespace Tls10
		{
			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.1
			namespace ProtocolVersion
			{
				struct ProtocolVersion
				{
					uint8_t major;
					uint8_t minor;
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.1
			namespace ContentType
			{

				enum ContentType : uint8_t
				{
					change_cipher_spec = 0x14,
					alert = 0x15,
					handshake = 0x16,
					application_data = 0x17
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.1
			struct TLSPlaintext
			{
				/// @brief The higher level protocol used to process the enclosed fragment.
				ContentType::ContentType type;

				/// @brief The version of the protocol being employed.
				ProtocolVersion::ProtocolVersion version;

				/// @brief The length (in bytes) of the following TLSPlaintext.fragment.
				/// The length should not exceed 2 ^ 14
				uint16_t length;

				/// @brief The application data. This data is transparent and treated as an
				/// independent block to be dealt with by the higher level protocol
				///	specified by the type field. Size of the vector MUST equal "length"
				std::vector<uint8_t> fragment;
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.2
			struct TLSCompressed
			{
				/// @brief The higher level protocol used to process the enclosed fragment.
				ContentType::ContentType type;

				/// @brief The version of the protocol being employed.
				ProtocolVersion::ProtocolVersion version;

				/// @brief The length (in bytes) of the following TLSCompressed.fragment.
				/// The length should not exceed 2 ^ 14 + 1024.
				uint16_t length;

				/// @brief The compressed form of TLSPlaintext.fragment.
				/// Size of the vector MUST equal "length"
				std::vector<uint8_t> fragment;
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.3
			struct TLSCiphertext
			{
				/// @brief The higher level protocol used to process the enclosed fragment.
				ContentType::ContentType type;

				/// @brief The version of the protocol being employed.
				ProtocolVersion::ProtocolVersion version;

				/// @brief The length (in bytes) of the following TLSCiphertext.fragment.
				/// The length may not exceed 2 ^ 14 + 2048.
				uint16_t length;

				/// @brief The encrypted form of TLSCompressed.fragment, with the MAC.
				/// Size of the vector MUST equal "length"
				// select (CipherSpec.cipher_type) {
				//   case stream: GenericStreamCipher;
				//   case block: GenericBlockCipher;
				// } fragment;
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.3.1

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.3.2

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.1
			struct ChangeCipherSpec
			{
				enum : uint8_t
				{
					change_cipher_spec = 1
				} type;
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2
			namespace AlertLevel
			{
				enum AlertLevel : uint8_t
				{
					warning = 1,
					fatal = 2,
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2
			namespace AlertDescription
			{
				enum AlertDescription : uint8_t
				{
					close_notify = 0x00,
					unexpected_message = 0x0a,
					bad_record_mac = 0x14,
					decryption_failed = 0x15,
					record_overflow = 0x16,
					decompression_failure = 0x1e,
					handshake_failure = 0x28,
					bad_certificate = 0x2a,
					unsupported_certificate = 0x2b,
					certificate_revoked = 0x2c,
					certificate_expired = 0x2d,
					certificate_unknown = 0x2e,
					illegal_parameter = 0x2f,
					unknown_ca = 0x30,
					access_denied = 0x31,
					decode_error = 0x32,
					decrypt_error = 0x31,
					export_restriction = 0x3c,
					protocol_version = 0x46,
					insufficient_security = 0x47,
					internal_error = 0x50,
					user_canceled = 0x5a,
					no_renegotiation = 0x64,
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.2
			struct Alert
			{
				AlertLevel::AlertLevel level;
				AlertDescription::AlertDescription description;
			};
		}
	}
}

