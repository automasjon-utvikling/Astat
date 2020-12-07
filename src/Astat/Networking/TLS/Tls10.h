#pragma once

#include "Astat/Astat.h"

namespace Astat
{
	namespace Networking
	{
		/// @brief https://tools.ietf.org/html/rfc2246
		namespace Tls10
		{
			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			namespace ConnectionEnd
			{
				enum ConnectionEnd
				{
					server,
					client
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			namespace BulkCipherAlgorithm
			{
				enum BulkCipherAlgorithm
				{
					null,
					rc4,
					rc2,
					des,
					des3,
					des40
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			namespace CipherType
			{
				enum CipherType
				{
					stream,
					block
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			namespace IsExportable
			{
				enum IsExportable
				{
					true_,
					client_
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			namespace MACAlgorithm
			{
				enum MACAlgorithm
				{
					null,
					md5,
					sha
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			namespace CompressionMethod
			{
				enum CompressionMethod : uint8_t
				{
					null = 0
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.1
			struct SecurityParameters
			{
				ConnectionEnd::ConnectionEnd entity;
				BulkCipherAlgorithm::BulkCipherAlgorithm bulk_cipher_algorithm;
				CipherType::CipherType cipher_type;
				uint8_t key_size;
				uint8_t key_material_length;
				IsExportable::IsExportable is_exportable;
				MACAlgorithm::MACAlgorithm mac_algorithm;
				uint8_t hash_size;
				CompressionMethod::CompressionMethod compression_algorithm;
				uint8_t master_secret[48];
				uint8_t client_random[32];
				uint8_t server_random[32];
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.1
			struct ProtocolVersion
			{
				uint8_t major;
				uint8_t minor;
			};

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
				ProtocolVersion version;

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
				ProtocolVersion version;

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
				ProtocolVersion version;

				/// @brief The length (in bytes) of the following TLSCiphertext.fragment.
				/// The length may not exceed 2 ^ 14 + 2048.
				uint16_t length;

				// Todo
				/// @brief The encrypted form of TLSCompressed.fragment, with the MAC.
				/// Size of the vector MUST equal "length"
				// select (CipherSpec.cipher_type) {
				//   case stream: GenericStreamCipher;
				//   case block: GenericBlockCipher;
				// } fragment;
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.3.1
			// Todo

			/// @brief https://tools.ietf.org/html/rfc2246#section-6.2.3.2
			// Todo

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

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4
			namespace HandshakeType
			{
				enum HandshakeType : uint8_t
				{
					hello_request = 0x00,
					client_hello = 0x01,
					server_hello = 0x02,
					certificate = 0x0b,
					server_key_exchange = 0x0c,
					certificate_request = 0x0d,
					server_hello_done = 0x0e,
					certificate_verify = 0x0f,
					client_key_exchange = 0x10,
					finished = 0x14
				};
			}

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4
			struct HandshakeBody
			{

			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4
			struct Handshake
			{
				HandshakeType::HandshakeType msg_type;
				uint24_t length;
				struct HandshakeBody body;
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.1.1
			struct HelloRequest : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.1.2
			struct ClientHello : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.1.3
			struct ServerHello : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.2
			struct Certificate : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.3
			struct ServerKeyExchange : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.4
			struct CertificateRequest : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.5
			struct ServerHelloDone : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.8
			struct CertificateVerify : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.7
			struct ClientKeyExchange : HandshakeBody
			{
				// Todo
			};

			/// @brief https://tools.ietf.org/html/rfc2246#section-7.4.9
			struct Finished : HandshakeBody
			{
				// Todo
			};
		}
	}
}

