#include "atpch.h"

#include "HttpServer.h"
#include "HttpError.h"

#include "Astat/Logging/Logger.h"
#include "Astat/Utils/FileUtils.h"

namespace Astat
{
	namespace Networking
	{
		namespace Http
		{
			void HttpServer::onClientConnect (SOCKET aClientSocketId)
			{
				Astat::Logger::Logger::sLog ("Connected: " + std::to_string (aClientSocketId));
			} // onClientConnect()

			void HttpServer::onClientDisconnect (SOCKET aClientSocketId)
			{
				Astat::Logger::Logger::sLog ("Disconnected: " + std::to_string (aClientSocketId));
			} // onClientDisconnect()

			void HttpServer::onClientMessage (SOCKET aClientSocketId, const char *aMessage)
			{
				//std::string cmessage = aMessage;
				//std::vector<char> cmessage(4096);
				//strncpy_s (&cmessage[0], aMessage, (size_t)4096);
				const char *cmessage = aMessage;
				//
				// TLS layer
				//
				if (cmessage[0] == 0x16)
				{
					std::cout << "TLS detected" << std::endl;
					if (cmessage[1] == 0x03 && cmessage[2] == 0x01)
					{
						std::cout << "v0301 (1.0)" << std::endl;
						uint16_t message_length = cmessage[3] << 8 | cmessage[4];
						if (cmessage[5] == 0x01) // ClientHello
						{
							std::cout << "ClientHello" << std::endl;
							uint32_t hello_length = cmessage[6] << 16 | cmessage[7] << 8 | cmessage[8];
							std::cout << "length: " << hello_length << std::endl;
							if (!(cmessage[9] == 0x03 && cmessage[10] == 0x03))
							{
								std::cout << "insufficient security alert" << std::endl;
								// Send insufficient security alert
								return;
							}
							std::vector<uint8_t> random;
							for (int i = 0; i < 32; i++)
							{
								random.push_back (cmessage[11 + i]);
							} // Next is 43

							std::stringstream ssrandom;
							for (size_t i = 0; i < 32; ++i)
							{
								ssrandom << std::setw (2) << std::setfill ('0') << std::hex << (int) random[i] << " ";
							}
							std::string srandom = ssrandom.str ();
							size_t posrandom = std::string::npos;
							// Search for the substring in string in a loop untill nothing is found
							while ((posrandom = srandom.find ("ffff")) != std::string::npos)
							{
								// If found then erase it from string
								srandom.erase (posrandom, 6);
							}

							std::cout << "random: " << srandom << std::endl;

							uint8_t legacy_session_id_length = cmessage[43];
							std::vector<uint8_t> legacy_session_id;
							for (int i = 0; i < legacy_session_id_length; i++) // Is it 32?
							{
								random.push_back (cmessage[44 + i]);
							} // Next is unknown
							
							uint16_t index = 44 + legacy_session_id_length;
							uint16_t cipher_suit_length = cmessage[index] << 8 | cmessage[index +1];
							index += 2;
							std::vector<uint16_t> cipher_suits;
							for (int i = 0; i < cipher_suit_length; i++)
							{
								cipher_suits.push_back (cmessage[index] << 8 | cmessage[index + 1]);
								index += 2;
							}
							uint8_t compression_methods_length = cmessage[index++];
							std::vector<uint8_t> compression_methods;
							for (int i = 0; i < compression_methods_length; i++)
							{
								compression_methods.push_back (cmessage[index++]);
							}

							uint16_t extensions_length = cmessage[index] << 8 | cmessage[index + 1];
							index += 2;
							std::vector<uint16_t> extensions;
							for (int i = 0; i < extensions_length; i++)
							{
								extensions.push_back (cmessage[index] << 8 | cmessage[index + 1]);
								index += 2;
							}

							// todo: get extension data from extensions

							std::stringstream ss;
							for (size_t i = 0; i < extensions_length; ++i)
							{
								ss << std::setw (2) << std::setfill ('0') << std::hex << (int) extensions[i] << " ";
							}
							std::string s = ss.str ();
							size_t pos = std::string::npos;
							// Search for the substring in string in a loop untill nothing is found
							while ((pos = s.find ("ffff")) != std::string::npos)
							{
								// If found then erase it from string
								s.erase (pos, 6);
							}
							std::cout << "\033[;31m" << s << "\033[0m" << std::endl;
						}
					}
				}

				std::istringstream iss (aMessage);
				std::vector<std::string> message ((std::istream_iterator<std::string> (iss)), std::istream_iterator<std::string> ());

				int status_code = 200;
				std::string file_content;
				
				//
				// Handling of the CONNECT-method
				//
				if (message.size () >= 6 && message[0] == "CONNECT")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the DELETE-method
				//
				else if (message.size () >= 6 && message[0] == "DELETE")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the GET-method
				//
				else if (message.size () >= 3 && message[0] == "GET")
				{
					std::string status_message;
					//
					// Redirects
					//
					if (message[1] == "/")
					{
						message[1] = "/index.htm";
					}

					//
					// Handle relation between the suffix of the requested file and its content type
					//
					std::vector<HttpFileType> known_file_types = {
						{".htm", "text/html", "text"},
						{".js", "text/javascript", "text"},
						{".css", "text/css", "text"},
						{".png", "image/png", "binary"},
						{".jpg", "image/jpeg", "binary"},
						{".svg", "image/svg+xml", "text"},
					};

					HttpFileType current_filetype ("", "", "");
					bool is_filetype_known = false;
					for (HttpFileType filetype : known_file_types)
					{
						if (
							// File ends with suffix ...
							message[1].size () >= filetype.suffix.size () &&
							message[1].compare (message[1].size () - filetype.suffix.size (), filetype.suffix.size (), filetype.suffix) == 0
							)
						{
							current_filetype.suffix = filetype.suffix;
							current_filetype.type = filetype.type;
							current_filetype.group = filetype.group;
							is_filetype_known = true;
							break;
						}
					}

					if (!is_filetype_known)
					{
						if (message[1].find ('.') == std::string::npos)
						{
							message[1].append (".htm");
							current_filetype.suffix = ".htm";
							current_filetype.type = "text/html";
							current_filetype.group = "text";
						}
						else
						{
							current_filetype.suffix = "";
							current_filetype.type = "application/octet-stream";
						}
					}

					//
					// Read the requested file
					//
					Utils::File file;
					if (current_filetype.group == "binary")
					{
						file.Assign ("./www/public" + message[1], Utils::File::EFileMode::BINARY);
					}
					else
					{
						file.Assign ("./www/public" + message[1]);
					}

					if ((long) file.Read (file_content) != NO_ERROR)
					{
						Astat::Logger::Logger::sLog ("Read Error -> 404 Not found");
						status_code = HttpError::GetNotFound (status_message);
					}

					//
					// Templating file inclutions
					//
					if (current_filetype.type == "text/html")
					{
						std::vector<std::string> matches;
						std::string s = file_content;
						std::smatch m;
						std::regex e ("\\{\\{ template\\.\\w+ \\}\\}");
						while (std::regex_search (s, m, e))
						{
							for (auto x : m)
							{
								matches.push_back (x);
							}
							s = m.suffix ().str ();
						}

						Utils::File template_file;
						for (std::string x : matches)
						{
							std::string template_name = x.substr (std::string ("{{ template.").length ());
							template_name.erase (template_name.length () - std::string (" }}").length ());
							template_name += ".template";
							template_file.Assign ("./www/public/templates/" + template_name);

							std::string r;
							if ((long) template_file.Read (r) != NO_ERROR)
							{
								Astat::Logger::Logger::sLog ("Template Read Error");
							}

							for (size_t pos = 0; ; pos += r.length ())
							{
								// Locate the substring to replace
								pos = file_content.find (x, pos);
								if (pos == std::string::npos)
								{
									break;
								}

								// Replace by erasing and inserting
								file_content.erase (pos, x.length ());
								file_content.insert (pos, r);
							}
						}
					}
					//
					// Templating variables
					//

					// Todo

					//
					// Construct the response
					//
					std::ostringstream oss;
					if (status_code == 200)
					{
						oss << "HTTP/1.1 " << status_code << " OK\r\n";
					}
					else
					{
						oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
						file_content = status_message;
					}
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << current_filetype.type << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					// 
					// Send the response
					//
					std::string output = oss.str ();
					size_t size = output.size () + 1;
					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the HEAD-method
				//
				else if (message.size () >= 4 && message[0] == "HEAD")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the OPTIONS-method
				//
				else if (message.size () >= 7 && message[0] == "OPTIONS")
				{
					std::ostringstream oss;
					oss << "HTTP/1.1 204 No Content\r\n";
					oss << "Allow: GET, OPTIONS\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "\r\n";

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the PATCH-method
				//
				else if (message.size () >= 5 && message[0] == "PATCH")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the POST-method
				//
				else if (message.size () >= 4 && message[0] == "POST")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the PUT-method
				//
				else if (message.size () >= 3 && message[0] == "PUT")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}

				//
				// Handling of the TRACE-method
				//
				else if (message.size () >= 5 && message[0] == "TRACE")
				{
					std::string status_message;
					status_code = HttpError::GetMethodNotAllowed (status_message);
					file_content = status_message;

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}
			} // onClientMessage()
		} // namespace Http
	} // namespace Networking
} // namespace Astat