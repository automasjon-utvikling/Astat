#include "atpch.h"
#include "HttpServer.h"

#include "Astat/Logging/Logger.h"

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

				std::string file_content = "";

				int status_code = 0;
				std::string file_name = "";

				std::string log_message = "Message: \n";
				for (std::string str : message)
				{
					log_message.append("\t").append(str).append("\n");
				}
				Astat::Logger::Logger::sLog(log_message);

				if (message.size() >= 3 && message[0] == "GET")
				{
#ifdef AT_LOGGING_FULL
					Astat::Logger::Logger::sLog("Message: GET " + message[1]);
#endif
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
						current_filetype.suffix = "";
						current_filetype.type = "application/octet-stream";
					}

					std::ifstream file;
					if(current_filetype.group == "binary"){
						file = std::ifstream("./www/public/" + message[1], std::ios::binary);
					}else{
						file = std::ifstream("./www/public/" + message[1]);
					}

					if (file.good())
					{
						std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
						file_content = str;
						status_code = 200;
						Astat::Logger::Logger::sLog("Message: GET " + message[1]);
					}
					else
					{
						Astat::Logger::Logger::sLog("Message: Unknown file request!: " + message[1]);
						std::ifstream file404("./www/messages/404.htm");
						if (file404.good())
						{
							std::string str((std::istreambuf_iterator<char>(file404)), std::istreambuf_iterator<char>());
							file_content = str;
							status_code = 404;
						}
						else
						{
							Astat::Logger::Logger::sLog("Message: File read failed!");
							file_content = "<h3>404/5xx: File not found</h3>";
							status_code = 500;
						}
						file404.close();
					}
					file.close();

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
					Astat::Logger::Logger::sLog("Message: POST");
				}

			}
		}
	}
}