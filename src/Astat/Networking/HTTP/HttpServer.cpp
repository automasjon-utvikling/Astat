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
			void HttpServer::onClientConnect(SOCKET aClientSocketId)
			{
				Astat::Logger::Logger::sLog("Connected: " + std::to_string(aClientSocketId));
			}

			void HttpServer::onClientDisconnect(SOCKET aClientSocketId)
			{
				Astat::Logger::Logger::sLog("Disconnected: " + std::to_string(aClientSocketId));
			}

			void HttpServer::onClientMessage(SOCKET aClientSocketId, const char* aMessage)
			{
				std::istringstream iss(aMessage);
				std::vector<std::string> message((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

				int status_code = 200;
				std::string file_content;

				std::string log_message = "Message: \n";
				for (std::string str : message)
				{
					log_message.append("\t").append(str).append("\n");
				}
				Astat::Logger::Logger::sLog(log_message);

				if (message.size() >= 3 && message[0] == "GET")
				{
					if (message[1] == "/")
					{
						message[1] = "/index.htm";
					}

					std::vector<HttpFileType> known_file_types = {
						{".htm", "text/html", "text"},
						{".js", "text/javascript", "text"},
						{".css", "text/css", "text"},
						{".png", "image/png", "binary"},
						{".jpg", "image/jpeg", "binary"},
						{".svg", "image/svg+xml", "text"},
					};

					HttpFileType current_filetype("", "", "");
					bool is_filetype_known = false;
					for (HttpFileType filetype : known_file_types) {
						if (
							message[1].size() >= filetype.suffix.size() &&
							message[1].compare(message[1].size() - filetype.suffix.size(), filetype.suffix.size(), filetype.suffix) == 0)
						{
							current_filetype.suffix = filetype.suffix;
							current_filetype.type = filetype.type;
							current_filetype.group = filetype.group;
							is_filetype_known = true;
							break;
						}
					}
					
					if(!is_filetype_known){
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

					Utils::File file;
					if (current_filetype.group == "binary")
					{
						Astat::Logger::Logger::sLog ("Read Binary");
						file.Assign("./www/public" + message[1], Utils::File::EFileMode::BINARY);
					}
					else
					{
						Astat::Logger::Logger::sLog ("Read Text");
						file.Assign("./www/public" + message[1]);
					}

					if ((long) file.Read (file_content) == NO_ERROR)
					{
						Astat::Logger::Logger::sLog ("Read OK");
					}
					else
					{
						Astat::Logger::Logger::sLog ("Read Error -> 404 Not found");
						status_code = HttpError::GetNotFound (file_content);
					}

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " OK\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << current_filetype.type << "\r\n";
					oss << "Content-Length: " << file_content.size() << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str();
					size_t size = output.size() + 1;

					execSendTo(aClientSocketId, output.c_str(), size);
				}
				else if (message.size() >= 4 && message[0] == "POST")
				{
					status_code = HttpError::GetNotImplemented (file_content);

					std::ostringstream oss;
					oss << "HTTP/1.1 " << status_code << " OK\r\n";
					oss << "Cache-Control: no-cache, private\r\n";
					oss << "Content-Type: " << "text/html" << "\r\n";
					oss << "Content-Length: " << file_content.size () << "\r\n";
					oss << "\r\n";
					oss << file_content;

					std::string output = oss.str ();
					size_t size = output.size () + 1;

					execSendTo (aClientSocketId, output.c_str (), size);
				}
			}
		}
	}
}