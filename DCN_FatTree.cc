/*
Title: DCN simulation using NS3
Description: DCN Fat Tree Architecture for 16 servers is created. Flow analysis using Static and ECMP routing is done.
			 Flow statistics and Packet capture files are generated. Flow statistics files can be viewed in NetAnim.
Programmer:
		Name				Date 
Amit Khandu Bhalerao		17 December 2016
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-helper.h"


using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("DCNusingNS3");

int main(int argc, char *argv[])
{
	CommandLine cmd;
	bool ECMProuting = true;
	cmd.AddValue ("ECMProuting", "ECMP routing (To enable type 'true') ", ECMProuting);
	cmd.Parse (argc, argv);
	  
	Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	
	Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting",BooleanValue(ECMProuting));
	
	uint32_t Corequeuesize,Leafqueuesize;
	Corequeuesize = 8;
	Leafqueuesize = 4;
	PointToPointHelper NodeToSW;
	NodeToSW.SetDeviceAttribute ("DataRate", StringValue ("10Gbps"));
	NodeToSW.SetChannelAttribute ("Delay", StringValue ("200ns"));
	
	PointToPointHelper SWToSW_50ns;
	SWToSW_50ns.SetDeviceAttribute ("DataRate", StringValue ("40Gbps"));
	SWToSW_50ns.SetChannelAttribute ("Delay", StringValue ("50ns"));
	SWToSW_50ns.SetQueue("ns3::DropTailQueue", "MaxPackets", UintegerValue(Corequeuesize)); 
	
	PointToPointHelper SWToSW_70ns;
	SWToSW_70ns.SetDeviceAttribute ("DataRate", StringValue ("40Gbps"));
	SWToSW_70ns.SetChannelAttribute ("Delay", StringValue ("70ns"));
	SWToSW_70ns.SetQueue("ns3::DropTailQueue", "MaxPackets", UintegerValue(Leafqueuesize)); 
	
	NodeContainer pod0,pod1,pod2,pod3,core;
	pod0.Create (8);
	pod1.Create (8);
	pod2.Create (8);
	pod3.Create (8);
	core.Create (4);
	
	InternetStackHelper Stack;
	Stack.Install( pod0);
	Stack.Install( pod1);
	Stack.Install( pod2);
	Stack.Install( pod3);
	Stack.Install( core);
	
	
	//Creating Topology
	NetDeviceContainer pod0_dev,pod0_dev2,pod0_dev3,pod0_dev4,pod0_dev5,pod0_dev6,pod0_dev7,pod0_dev8;
	pod0_dev = NodeToSW.Install( pod0.Get(0), pod0.Get(4));
	pod0_dev2 = NodeToSW.Install( pod0.Get(1), pod0.Get(4));
	pod0_dev3 = NodeToSW.Install( pod0.Get(2), pod0.Get(5));
	pod0_dev4 = NodeToSW.Install( pod0.Get(3), pod0.Get(5));
	pod0_dev5 = SWToSW_50ns.Install( pod0.Get(4), pod0.Get(6));
	pod0_dev6 = SWToSW_70ns.Install( pod0.Get(4), pod0.Get(7));
	pod0_dev7 = SWToSW_50ns.Install( pod0.Get(5), pod0.Get(6));
	pod0_dev8 = SWToSW_70ns.Install( pod0.Get(5), pod0.Get(7));
	
	NetDeviceContainer pod1_dev,pod1_dev2,pod1_dev3,pod1_dev4,pod1_dev5,pod1_dev6,pod1_dev7,pod1_dev8;
	pod1_dev = NodeToSW.Install( pod1.Get(0), pod1.Get(4));
	pod1_dev2 = NodeToSW.Install( pod1.Get(1), pod1.Get(4));
	pod1_dev3 = NodeToSW.Install( pod1.Get(2), pod1.Get(5));
	pod1_dev4 = NodeToSW.Install( pod1.Get(3), pod1.Get(5));
	pod1_dev5 = SWToSW_50ns.Install( pod1.Get(4), pod1.Get(6));
	pod1_dev6 = SWToSW_70ns.Install( pod1.Get(4), pod1.Get(7));
	pod1_dev7 = SWToSW_50ns.Install( pod1.Get(5), pod1.Get(6));
	pod1_dev8 = SWToSW_70ns.Install( pod1.Get(5), pod1.Get(7));
	
	NetDeviceContainer pod2_dev,pod2_dev2,pod2_dev3,pod2_dev4,pod2_dev5,pod2_dev6,pod2_dev7,pod2_dev8;
	pod2_dev = NodeToSW.Install( pod2.Get(0), pod2.Get(4));
	pod2_dev2 = NodeToSW.Install( pod2.Get(1), pod2.Get(4));
	pod2_dev3 = NodeToSW.Install( pod2.Get(2), pod2.Get(5));
	pod2_dev4 = NodeToSW.Install( pod2.Get(3), pod2.Get(5));
	pod2_dev5 = SWToSW_50ns.Install( pod2.Get(4), pod2.Get(6));
	pod2_dev6 = SWToSW_70ns.Install( pod2.Get(4), pod2.Get(7));
	pod2_dev7 = SWToSW_50ns.Install( pod2.Get(5), pod2.Get(6));
	pod2_dev8 = SWToSW_70ns.Install( pod2.Get(5), pod2.Get(7));
	
	NetDeviceContainer pod3_dev,pod3_dev2,pod3_dev3,pod3_dev4,pod3_dev5,pod3_dev6,pod3_dev7,pod3_dev8;
	pod3_dev = NodeToSW.Install( pod3.Get(0), pod3.Get(4));
	pod3_dev2 = NodeToSW.Install( pod3.Get(1), pod3.Get(4));
	pod3_dev3 = NodeToSW.Install( pod3.Get(2), pod3.Get(5));
	pod3_dev4 = NodeToSW.Install( pod3.Get(3), pod3.Get(5));
	pod3_dev5 = SWToSW_50ns.Install( pod3.Get(4), pod3.Get(6));
	pod3_dev6 = SWToSW_70ns.Install( pod3.Get(4), pod3.Get(7));
	pod3_dev7 = SWToSW_50ns.Install( pod3.Get(5), pod3.Get(6));
	pod3_dev8 = SWToSW_70ns.Install( pod3.Get(5), pod3.Get(7));
	

	//Core router connections
	NetDeviceContainer core_dev,core_dev2,core_dev3,core_dev4,core_dev5,core_dev6,core_dev7,core_dev8;
	NetDeviceContainer core_dev9,core_dev10,core_dev11,core_dev12,core_dev13,core_dev14,core_dev15,core_dev16;
	core_dev = SWToSW_50ns.Install( pod0.Get(6), core.Get(0));
	core_dev2 = SWToSW_50ns.Install( pod1.Get(6), core.Get(0));
	core_dev3 = SWToSW_50ns.Install( pod2.Get(6), core.Get(0));
	core_dev4 = SWToSW_50ns.Install( pod3.Get(6), core.Get(0));
	
	core_dev5 = SWToSW_50ns.Install( pod0.Get(6), core.Get(1));
	core_dev6 = SWToSW_50ns.Install( pod1.Get(6), core.Get(1));
	core_dev7 = SWToSW_50ns.Install( pod2.Get(6), core.Get(1));
	core_dev8 = SWToSW_50ns.Install( pod3.Get(6), core.Get(1));
	
	core_dev9 = SWToSW_50ns.Install( pod0.Get(7), core.Get(2));
	core_dev10 = SWToSW_50ns.Install( pod1.Get(7), core.Get(2));
	core_dev11 = SWToSW_50ns.Install( pod2.Get(7), core.Get(2));
	core_dev12 = SWToSW_50ns.Install( pod3.Get(7), core.Get(2));
	
	core_dev13 = SWToSW_50ns.Install( pod0.Get(7), core.Get(3));
	core_dev14 = SWToSW_50ns.Install( pod1.Get(7), core.Get(3));
	core_dev15 = SWToSW_50ns.Install( pod2.Get(7), core.Get(3));
	core_dev16 = SWToSW_50ns.Install( pod3.Get(7), core.Get(3));
		
	//Assigning the IP address
	
	Ipv4AddressHelper address;
	Ipv4InterfaceContainer pod0_Iface,pod0_Iface2,pod0_Iface3,pod0_Iface4,pod0_Iface5,pod0_Iface6,pod0_Iface7,pod0_Iface8;
	address.SetBase("10.0.0.0","255.255.255.0");
	pod0_Iface = address.Assign (pod0_dev);
	
	address.SetBase("10.0.1.0","255.255.255.0");
	pod0_Iface2 = address.Assign(pod0_dev2);
	
	address.SetBase("10.0.2.0","255.255.255.0");
	pod0_Iface3 = address.Assign(pod0_dev3);
	
	address.SetBase("10.0.3.0","255.255.255.0");
	pod0_Iface4 = address.Assign(pod0_dev4);
	
	address.SetBase("10.1.0.0","255.255.0.0");
	pod0_Iface5 = address.Assign(pod0_dev5);

	address.SetBase("10.2.0.0","255.255.0.0");
	pod0_Iface6 = address.Assign(pod0_dev6);

	address.SetBase("10.1.1.0","255.255.255.0");
	pod0_Iface7 = address.Assign(pod0_dev7);

	address.SetBase("10.2.1.0","255.255.255.0");
	pod0_Iface8 = address.Assign(pod0_dev8);
	
	Ipv4InterfaceContainer pod1_Iface,pod1_Iface2,pod1_Iface3,pod1_Iface4,pod1_Iface5,pod1_Iface6,pod1_Iface7,pod1_Iface8;
	address.SetBase("20.0.0.0","255.255.255.0");
	pod1_Iface = address.Assign (pod1_dev);
	
	address.SetBase("20.0.1.0","255.255.255.0");
	pod1_Iface2 = address.Assign(pod1_dev2);
	
	address.SetBase("20.0.2.0","255.255.255.0");
	pod1_Iface3 = address.Assign(pod1_dev3);
	
	address.SetBase("20.0.3.0","255.255.255.0");
	pod1_Iface4 = address.Assign(pod1_dev4);
	
	address.SetBase("20.1.0.0","255.255.0.0");
	pod1_Iface5 = address.Assign(pod1_dev5);

	address.SetBase("20.2.0.0","255.255.0.0");
	pod1_Iface6 = address.Assign(pod1_dev6);

	address.SetBase("20.1.1.0","255.255.255.0");
	pod1_Iface7 = address.Assign(pod1_dev7);

	address.SetBase("20.2.1.0","255.255.255.0");
	pod1_Iface8 = address.Assign(pod1_dev8);
	
	Ipv4InterfaceContainer pod2_Iface,pod2_Iface2,pod2_Iface3,pod2_Iface4,pod2_Iface5,pod2_Iface6,pod2_Iface7,pod2_Iface8;
	address.SetBase("30.0.0.0","255.255.255.0");
	pod2_Iface = address.Assign (pod2_dev);
	
	address.SetBase("30.0.1.0","255.255.255.0");
	pod2_Iface2 = address.Assign(pod2_dev2);
	
	address.SetBase("30.0.2.0","255.255.255.0");
	pod2_Iface3 = address.Assign(pod2_dev3);
	
	address.SetBase("30.0.3.0","255.255.255.0");
	pod2_Iface4 = address.Assign(pod2_dev4);

	address.SetBase("30.1.0.0","255.255.0.0");
	pod2_Iface5 = address.Assign(pod2_dev5);

	address.SetBase("30.2.0.0","255.255.0.0");
	pod2_Iface6 = address.Assign(pod2_dev6);

	address.SetBase("30.1.1.0","255.255.255.0");
	pod2_Iface7 = address.Assign(pod2_dev7);

	address.SetBase("30.2.1.0","255.255.255.0");
	pod2_Iface8 = address.Assign(pod2_dev8);
	
	Ipv4InterfaceContainer pod3_Iface,pod3_Iface2,pod3_Iface3,pod3_Iface4,pod3_Iface5,pod3_Iface6,pod3_Iface7,pod3_Iface8;
	address.SetBase("40.0.0.0","255.255.255.0");
	pod3_Iface = address.Assign (pod3_dev);
	
	address.SetBase("40.0.1.0","255.255.255.0");
	pod3_Iface2 = address.Assign(pod3_dev2);
	
	address.SetBase("40.0.2.0","255.255.255.0");
	pod3_Iface3 = address.Assign(pod3_dev3);
	
	address.SetBase("40.0.3.0","255.255.255.0");
	pod3_Iface4 = address.Assign(pod3_dev4);
	
	address.SetBase("40.1.0.0","255.255.0.0");
	pod3_Iface5 = address.Assign(pod3_dev5);

	address.SetBase("40.2.0.0","255.255.0.0");
	pod3_Iface6 = address.Assign(pod3_dev6);

	address.SetBase("40.1.1.0","255.255.255.0");
	pod3_Iface7 = address.Assign(pod3_dev7);

	address.SetBase("40.2.1.0","255.255.255.0");
	pod3_Iface8 = address.Assign(pod3_dev8);
	
	//Core router Ifaces
	Ipv4InterfaceContainer core_Iface,core_Iface2,core_Iface3,core_Iface4,core_Iface5,core_Iface6,core_Iface7,core_Iface8;
	Ipv4InterfaceContainer core_Iface9,core_Iface10,core_Iface11,core_Iface12,core_Iface13,core_Iface14,core_Iface15,core_Iface16;
	
	address.SetBase("50.0.1.0","255.255.255.0");
	core_Iface = address.Assign(core_dev);

	address.SetBase("50.1.2.0","255.255.255.0");
	core_Iface2 = address.Assign(core_dev2);

	address.SetBase("50.1.3.0","255.255.255.0");
	core_Iface3 = address.Assign(core_dev3);

	address.SetBase("50.1.4.0","255.255.255.0");
	core_Iface4 = address.Assign(core_dev4);
	
	address.SetBase("50.2.1.0","255.255.255.0");
	core_Iface5 = address.Assign(core_dev5);

	address.SetBase("50.2.2.0","255.255.255.0");
	core_Iface6 = address.Assign(core_dev6);

	address.SetBase("50.2.3.0","255.255.255.0");
	core_Iface7 = address.Assign(core_dev7);

	address.SetBase("50.2.4.0","255.255.255.0");
	core_Iface8 = address.Assign(core_dev8);
	
	address.SetBase("50.3.1.0","255.255.255.0");
	core_Iface9 = address.Assign(core_dev9);

	address.SetBase("50.3.2.0","255.255.255.0");
	core_Iface10 = address.Assign(core_dev10);

	address.SetBase("50.3.3.0","255.255.255.0");
	core_Iface11 = address.Assign(core_dev11);

	address.SetBase("50.3.4.0","255.255.255.0");
	core_Iface12 = address.Assign(core_dev12);
	
	address.SetBase("50.4.1.0","255.255.255.0");
	core_Iface13 = address.Assign(core_dev13);

	address.SetBase("50.4.2.0","255.255.255.0");
	core_Iface14 = address.Assign(core_dev14);

	address.SetBase("50.4.3.0","255.255.255.0");
	core_Iface15 = address.Assign(core_dev15);

	address.SetBase("50.4.4.0","255.255.255.0");
	core_Iface16 = address.Assign(core_dev16);
	
	//Routing tables
	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();
	//Applications

	UdpEchoServerHelper echoServer (9);
	ApplicationContainer serverApps,serverApps2,serverApps3,serverApps4;
	serverApps = echoServer.Install (pod0.Get (0));
	serverApps2 = echoServer.Install (pod0.Get (1));
	serverApps3 = echoServer.Install (pod1.Get (2));
	serverApps4 = echoServer.Install (pod1.Get (3));
	serverApps.Start (Seconds (1.0));
	serverApps.Stop (Seconds (10.1));
	serverApps2.Start (Seconds (1.0));
	serverApps2.Stop (Seconds (3.1));
	serverApps3.Start (Seconds (1.0));
	serverApps3.Stop (Seconds (3.1));
	serverApps4.Start (Seconds (1.0));
	serverApps4.Stop (Seconds (3.1));
	
	UdpEchoClientHelper echoClient (pod1_Iface3.GetAddress (0), 9);
	echoClient.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient.SetAttribute ("Interval", TimeValue (NanoSeconds (80)));
	echoClient.SetAttribute ("PacketSize", UintegerValue (100));
	
	UdpEchoClientHelper echoClient2 (pod1_Iface4.GetAddress (0), 9);
	echoClient2.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient2.SetAttribute ("Interval", TimeValue (NanoSeconds (60)));
	echoClient2.SetAttribute ("PacketSize", UintegerValue (100));
	
	UdpEchoClientHelper echoClient3 (pod0_Iface.GetAddress (0), 9);
	echoClient3.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient3.SetAttribute ("Interval", TimeValue (NanoSeconds (70)));
	echoClient3.SetAttribute ("PacketSize", UintegerValue (100));
	
	UdpEchoClientHelper echoClient4 (pod0_Iface2.GetAddress (0), 9);
	echoClient4.SetAttribute ("MaxPackets", UintegerValue (1000));
	echoClient4.SetAttribute ("Interval", TimeValue (NanoSeconds (85)));
	echoClient4.SetAttribute ("PacketSize", UintegerValue (100));
	

	ApplicationContainer clientApps, clientApps2,clientApps3,clientApps4;
	clientApps = echoClient.Install (pod2.Get (0));
	clientApps2 = echoClient2.Install (pod2.Get (1));
	clientApps3 = echoClient3.Install (pod3.Get (1));
	clientApps4 = echoClient4.Install (pod3.Get (2));
	

	clientApps.Start (Seconds (1.5));
	clientApps.Stop (Seconds (2.5));
	clientApps2.Start (Seconds (1.5));
	clientApps2.Stop (Seconds (2.5));
	clientApps3.Start (Seconds (1.5));
	clientApps3.Stop (Seconds (2.5));
	clientApps4.Start (Seconds (1.5));
	clientApps4.Stop (Seconds (2.5));
	

	//tcp flow
	int tcpSegmentSize = 1024; 
	uint32_t maxBytes = 1000000; // 0 means "unlimited"
	Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
	Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (0)); 
	uint16_t port = 80,port2 = 90; 
	Address sinkAaddr(InetSocketAddress (Ipv4Address::GetAny (), port)); 
	Address sinkAaddr2(InetSocketAddress (Ipv4Address::GetAny (), port2)); 
	Address sinkAaddr3(InetSocketAddress (Ipv4Address::GetAny (), port)); 
	Address sinkAaddr4(InetSocketAddress (Ipv4Address::GetAny (), port2)); 
	PacketSinkHelper sink ("ns3::TcpSocketFactory", sinkAaddr); 
	PacketSinkHelper sink2 ("ns3::TcpSocketFactory", sinkAaddr2); 		
	PacketSinkHelper sink3 ("ns3::TcpSocketFactory", sinkAaddr3); 
	PacketSinkHelper sink4 ("ns3::TcpSocketFactory", sinkAaddr4); 		
	ApplicationContainer sinkApp = sink.Install (pod0.Get(2)); 
	ApplicationContainer sinkApp2 = sink2.Install (pod0.Get(3)); 
	ApplicationContainer sinkApp3 = sink3.Install (pod1.Get(0)); 
	ApplicationContainer sinkApp4 = sink4.Install (pod1.Get(1)); 
	sinkApp.Start (Seconds (1)); 
	sinkApp.Stop (Seconds (2.5));
	sinkApp2.Start (Seconds (1)); 
	sinkApp2.Stop (Seconds (2.5));
	sinkApp3.Start (Seconds (1)); 
	sinkApp3.Stop (Seconds (2.5));
	sinkApp4.Start (Seconds (1)); 
	sinkApp4.Stop (Seconds (2.5));
	
	Address sinkAddr(InetSocketAddress(pod0_Iface3.GetAddress (0), port)); 
	Address sinkAddr2(InetSocketAddress(pod0_Iface4.GetAddress (0), port2)); 
 	Address sinkAddr3(InetSocketAddress(pod1_Iface.GetAddress (0), port)); 
	Address sinkAddr4(InetSocketAddress(pod1_Iface2.GetAddress (0), port2)); 
 
	BulkSendHelper sourceAhelper ("ns3::TcpSocketFactory", sinkAddr);
	BulkSendHelper sourceAhelper2 ("ns3::TcpSocketFactory", sinkAddr2); 
	BulkSendHelper sourceAhelper3 ("ns3::TcpSocketFactory", sinkAddr3);
	BulkSendHelper sourceAhelper4 ("ns3::TcpSocketFactory", sinkAddr4); 
	sourceAhelper.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper2.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper2.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper3.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper3.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper4.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper4.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	ApplicationContainer sourceAppsA = sourceAhelper.Install (pod3.Get (0)); 
	ApplicationContainer sourceAppsA2 = sourceAhelper2.Install (pod3.Get (3)); 
	ApplicationContainer sourceAppsA3 = sourceAhelper3.Install (pod2.Get (2)); 
	ApplicationContainer sourceAppsA4 = sourceAhelper4.Install (pod2.Get (3)); 
	sourceAppsA.Start (Seconds (1.5));
	sourceAppsA.Stop (Seconds (2.5));
	sourceAppsA2.Start (Seconds (1.5));
	sourceAppsA2.Stop (Seconds (2.5));
	sourceAppsA3.Start (Seconds (1.5));
	sourceAppsA3.Stop (Seconds (2.5));
	sourceAppsA4.Start (Seconds (1.5));
	sourceAppsA4.Stop (Seconds (2.5));
	
	//NodeToSW.EnablePcapAll ("FatTree");
	NodeToSW.EnablePcapAll("DCN_FatTree_Pcap");
	
		
	//Flow Statstics
	FlowMonitorHelper flowmonHelper;
	flowmonHelper.InstallAll();
	
	AnimationInterface anim ("animation.xml");
	anim.SetConstantPosition(pod0.Get(0),1.0, 20.0);
	anim.SetConstantPosition(pod0.Get(1),2.0, 20.0);
	anim.SetConstantPosition(pod0.Get(2),3.0, 20.0);
	anim.SetConstantPosition(pod0.Get(3),4.0, 20.0);
	anim.SetConstantPosition(pod0.Get(4),1.5, 16.0);
	anim.SetConstantPosition(pod0.Get(5),3.5, 16.0);
	anim.SetConstantPosition(pod0.Get(6),1.5, 12.0);
	anim.SetConstantPosition(pod0.Get(7),3.5, 12.0);
	
	anim.SetConstantPosition(pod1.Get(0),6.0, 20.0);
	anim.SetConstantPosition(pod1.Get(1),7.0, 20.0);
	anim.SetConstantPosition(pod1.Get(2),8.0, 20.0);
	anim.SetConstantPosition(pod1.Get(3),9.0, 20.0);
	anim.SetConstantPosition(pod1.Get(4),6.5, 16.0);
	anim.SetConstantPosition(pod1.Get(5),8.5, 16.0);
	anim.SetConstantPosition(pod1.Get(6),6.5, 12.0);
	anim.SetConstantPosition(pod1.Get(7),8.5, 12.0);
	
	//NodeTo
	anim.SetConstantPosition(pod2.Get(0),11.0, 20.0);
	anim.SetConstantPosition(pod2.Get(1),12.0, 20.0);
	anim.SetConstantPosition(pod2.Get(2),13.0, 20.0);
	anim.SetConstantPosition(pod2.Get(3),14.0, 20.0);
	anim.SetConstantPosition(pod2.Get(4),11.5, 16.0);
	anim.SetConstantPosition(pod2.Get(5),13.5, 16.0);
	anim.SetConstantPosition(pod2.Get(6),11.5, 12.0);
	anim.SetConstantPosition(pod2.Get(7),13.5, 12.0);
	
	anim.SetConstantPosition(pod3.Get(0),16.0, 20.0);
	anim.SetConstantPosition(pod3.Get(1),17.0, 20.0);
	anim.SetConstantPosition(pod3.Get(2),18.0, 20.0);
	anim.SetConstantPosition(pod3.Get(3),19.0, 20.0);
	anim.SetConstantPosition(pod3.Get(4),16.5, 16.0);
	anim.SetConstantPosition(pod3.Get(5),18.5, 16.0);
	anim.SetConstantPosition(pod3.Get(6),16.5, 12.0);
	anim.SetConstantPosition(pod3.Get(7),18.5, 12.0);
	
	anim.SetConstantPosition(core.Get(0),2.5, 7.0);
	anim.SetConstantPosition(core.Get(1),7.5, 7.0);
	anim.SetConstantPosition(core.Get(2),12.5, 7.0);
	anim.SetConstantPosition(core.Get(3),17.5, 7.0);
			
	Simulator::Stop (Seconds (2.0));
	Simulator::Run ();
  	NS_LOG_INFO ("Running the Simulation.");
	flowmonHelper.SerializeToXmlFile ("DCN_FatTree_FlowStat.flowmon", true, true);
  	NS_LOG_INFO ("Flowmon file creating.");
  	NS_LOG_INFO ("Done.");
	Simulator::Destroy ();

	return 0;

}
