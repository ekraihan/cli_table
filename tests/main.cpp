
#include "../cli_table.h"
#include <iostream>
#include <string>

int main()
{
    // std::vector<int> columnWidths = ;
    TablePrinter tp({24, 10,75,55});
    tp.print_row({
        "2020-03-16T06:50:17.863Z",
        "STATUS",
        "dfsfdfdfd",
        "purecloudcomm\non::Packet\nTracer::long_function_name("
    });

    std::string aSipString = R"(INVITE sip:bob@biloxi.example.com SIP/2.0
Via: SIP/2.0/TCP client.atlanta.example.com:5060;branch=z9hG4bK74bf9
Max-Forwards: 70
From: Alice <sip:alice@atlanta.example.com>;tag=9fxced76sl
To: Bob <sip:bob@biloxi.example.com>
Call-ID: 3848276298220188511@atlanta.example.com
CSeq: 2 INVITE
Contact: <sip:alice@client.atlanta.example.com;transport=tcp>
Diversion: Carol <sip:carol@atlanta.example.com>;privacy=off;reason=no-answer;counter=1;screen=no
Remote-Party-ID: Alice <sip:alice@atlanta.example.com>
P-Asserted-Identity: Alice <sip:alice@atlanta.example.com>
P-Charge-Info: <sip:eve@atlanta.example.com>
P-Source-Device: 216.3.128.12
Content-Type: application/sdp
Content-Length: 151
X-BroadWorks-DNC: network-address=sip:+9876543210@127.0.0.101;user=phone
User-Agent: X-Lite release 1104o stamp 56125 v=0 o=alice 2890844526 2890844526 IN IP4 client.atlanta.example.com s=- c=IN IP4 192.0.2.101 t=0 0 m=audio 49172 RTP/AVP 0 a=rtpmap:0 PCMU/8000)";

    std::string string1 = "2020-03-16T06:50:17.863Z";
    std::string string2 = "INFO";
    std::string string3 = "purecloudcommon::PacketTracer::long_function_name()";
    for (int i = 0; i < 10000; ++i)
    {
        tp.print_row({
            string1,
            string2,
            aSipString,
            string3
        });
    }

    tp.print_row({
        "2020-03-16T06:50:17.863Z",
        "WARNING",
        "a message inside cuz thats where bad things happen",
        "purecloudcommon::PacketTracer::long_function_name()"
    });

    tp.print_row({
        "2020-03-16T06:50:17.863Z",
        "ERROR",
        "a message inside cuz thats where bad things happen",
        "purecloudcommon::PacketTracer::long_function_name()"
    }, "1;31");

    return 0;
}