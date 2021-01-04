using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.ComponentModel;
using System.IO;

using static System.Console;
using static System.Environment;
using static System.IO.Path;

namespace Client
{
    class Program
    {
        public static async Task Main(string[] args)
        {
            int port = 8989;
            string serverIP;
            string PROMPT = ">>";

            string message;

            Write("Please enter server address: ");
            serverIP = ReadLine();

            IPAddress address = IPAddress.Parse(serverIP);

            bool done = false;

            while (!done)
            {
                using (TcpClient client = new TcpClient())
                {
                    client.Connect(address, port);
                    if (client.Connected)
                    {
                        WriteLine("Connected");
                    }

                    Write(PROMPT);
                    message = ReadLine();

                    var bytes = Encoding.ASCII.GetBytes(message);
                    var greeting = Encoding.ASCII.GetBytes("csharp");

                    using (var requestStream = client.GetStream())
                    {
                        await requestStream.WriteAsync(greeting, 0, greeting.Length);
                        await requestStream.WriteAsync(bytes, 0, bytes.Length);
                        if(message == "exit")
                        {
                            done = true;
                            continue;
                        }
                        var responseBytes = new byte[1024*8];

                        
                        
                        
                        //read file length
                        await requestStream.ReadAsync(responseBytes, 0, 255);
                        string fileSizeString = Encoding.ASCII.GetString(responseBytes);
                        int fileSizeInt;
                        Int32.TryParse(fileSizeString, out fileSizeInt);

                        Console.WriteLine($"File size: {fileSizeInt}");

                       
                        Array.Clear(responseBytes, 0, responseBytes.Length);
                        await requestStream.ReadAsync(responseBytes, 0, fileSizeInt);

                        string fileString = Encoding.ASCII.GetString(responseBytes);
                        //WriteLine($"Recieved data: {fileString}");
                        



                        

                       
                        //writing recieved data to file
                        string dummyFile = Combine(CurrentDirectory, "dummy_recieved.txt");
                        StreamWriter dummyText = File.CreateText(dummyFile);
                        dummyText.Write(fileString);
                        dummyText.Close();
                        done = true;
                        WriteLine("closing client");
                    }


                    
                }
            }
            return;
        }

        
    }
}
