/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/gpcr-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/wifi-module.h"
#include "ns3/v4ping-helper.h"
#include "ns3/udp-echo-server.h"
#include "ns3/udp-echo-client.h"
#include "ns3/udp-echo-helper.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include <iostream>
#include <cmath>
#include "ns3/netanim-module.h"

using namespace ns3;

class GpcrExample
{
public:
  GpcrExample ();
  /// Configure script parameters, \return true on successful configuration
  bool Configure (int argc, char **argv);
  /// Run simulation
  void Run ();
  /// Report results
  void Report (std::ostream & os);

private:
  ///\name parameters
  //\{
  /// Number of nodes
  uint32_t size;
  /// Width of the Node Grid
  uint32_t gridWidth;
  /// Distance between nodes, meters
  double step;
  /// Simulation time, seconds
  double totalTime;
  /// Write per-device PCAP traces if true
  bool pcap;
  //\}

  ///\name network
  //\{
  NodeContainer nodes;
  NetDeviceContainer devices;
  Ipv4InterfaceContainer interfaces;
  //\}

private:
  void CreateNodes ();
  void CreateDevices ();
  void InstallInternetStack ();
  void InstallApplications ();
};

int main (int argc, char **argv)
{
  GpcrExample test;
  if (! test.Configure(argc, argv))
    NS_FATAL_ERROR ("Configuration failed. Aborted.");

  test.Run ();
  test.Report (std::cout);
  return 0;
}

//-----------------------------------------------------------------------------
GpcrExample::GpcrExample () :
  // Number of Nodes
  size (200),
  // Grid Width
  gridWidth(5),
  // Distance between nodes
  step (10), //TODO Distance changed to the limit between nodes: test to see if there are transmitions
  // Simulation time
  totalTime (50),
  // Generate capture files for each node
  pcap (true)
{
}

bool
GpcrExample::Configure (int argc, char **argv)
{
  // Enable GPCR logs by default. Comment this if too noisy
  //LogComponentEnable("GpcrRoutingProtocol", LOG_LEVEL_ALL);

  SeedManager::SetSeed(12345);
  CommandLine cmd;

  cmd.AddValue ("pcap", "Write PCAP traces.", pcap);
  cmd.AddValue ("size", "Number of nodes.", size);
  cmd.AddValue ("time", "Simulation time, s.", totalTime);
  cmd.AddValue ("step", "Grid step, m", step);

  cmd.Parse (argc, argv);
  return true;
}

void
GpcrExample::Run ()
{
//  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", UintegerValue (1)); // enable rts cts all the time.
  CreateNodes ();
  CreateDevices ();
  InstallInternetStack ();
  InstallApplications ();

  GpcrHelper gpcr;
  gpcr.Set ("LocationServiceName", StringValue ("GOD"));
  gpcr.Install ();

  std::cout << "Starting simulation for " << totalTime << " s ...\n";
AnimationInterface anim ("animation_gpcr_test_diff200.xml");
anim.EnablePacketMetadata (true);

  Simulator::Stop (Seconds (totalTime));
  Simulator::Run ();
  Simulator::Destroy ();
}

void
GpcrExample::Report (std::ostream &)
{
}

void
GpcrExample::CreateNodes ()
{
  std::cout << "Creating " << (unsigned)size << " nodes " << step << " m apart.\n";
  nodes.Create (size);
  // Name nodes
  for (uint32_t i = 0; i < size; ++i)
     {
       std::ostringstream os;
       os << "node-" << i;
       Names::Add (os.str (), nodes.Get (i));
     }

  NodeContainer server;
  server.Add(nodes.Get(size-1));
  MobilityHelper mobility_server;
  mobility_server.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
                                "X", StringValue ("ns3::UniformRandomVariable[Min=50.0|Max=50.0]"),
                                "Y", StringValue ("ns3::UniformRandomVariable[Min=50.0|Max=50.0]"),
                                "Z", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=0.0]"));
//  mobility_server.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility_server.Install (server);


  // Create static grid
  MobilityHelper mobility;
/*  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                "MinX", DoubleValue (0.0),
                                "MinY", DoubleValue (0.0),
                                "DeltaX", DoubleValue (step),
                                "DeltaY", DoubleValue (step),
                                "GridWidth", UintegerValue (gridWidth),
                                "LayoutType", StringValue ("RowFirst"));
*/
  mobility.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
                                "X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                "Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                "Z", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=0.0]"));
//  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Mode", StringValue ("Time"),
                             "Time", StringValue ("2s"),
                             "Speed", StringValue ("ns3::UniformRandomVariable[Min=5.0|Max=30.0]"),
                             "Bounds", RectangleValue (Rectangle (0.0, 100.0, 0.0, 100.0)));

  for (uint32_t i = 0; i < (size-1); i++)
     {
        mobility.Install (nodes.Get(i));
     }

  mobility.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
                                "X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                "Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"),
                                "Z", StringValue ("ns3::UniformRandomVariable[Min=10.0|Max=10.0]"));

  for (uint32_t i = 0; i < (size-1); i=i+10)
     {
        mobility.Install (nodes.Get(i));
     }
}

void
GpcrExample::CreateDevices ()
{
  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  wifiMac.SetType ("ns3::AdhocWifiMac");
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  wifiPhy.Set ("TxPowerStart",DoubleValue (20.0));
  wifiPhy.Set ("TxPowerEnd", DoubleValue (20.0));
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
wifiChannel.AddPropagationLoss ("ns3::TwoRayGroundPropagationLossModel", "HeightAboveZ", DoubleValue (2.0));
  wifiPhy.SetChannel (wifiChannel.Create ());

  WifiHelper wifi = WifiHelper::Default ();
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("OfdmRate6Mbps"), "RtsCtsThreshold", UintegerValue (1492));
  devices = wifi.Install (wifiPhy, wifiMac, nodes);

  if (pcap)
    {
      wifiPhy.EnablePcapAll (std::string ("gpcr"));
    }
}

void
GpcrExample::InstallInternetStack ()
{
  GpcrHelper gpcr;
  // you can configure GPCR attributes here using gpcr.Set(name, value)
  InternetStackHelper stack;
  stack.SetRoutingHelper (gpcr);
  stack.Install (nodes);
  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.255.0.0");
  interfaces = address.Assign (devices);
}

void
GpcrExample::InstallApplications ()
{

  uint16_t port = 9;  // well-known echo port number
  uint32_t packetSize = 1024; // size of the packets being transmitted
  uint32_t maxPacketCount = 500; // number of packets to transmit
  Time interPacketInterval = Seconds (0.5); // interval between packet transmissions

  // Set-up  a server Application on the bottom-right node of the grid
  UdpEchoServerHelper server (port);
  uint16_t serverPosition = size-1; //bottom right
  ApplicationContainer apps = server.Install (nodes.Get(serverPosition));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (totalTime-0.1));

  // Set-up a client Application, connected to 'server', to be run on the top-left node of the grid
  UdpEchoClientHelper client (interfaces.GetAddress (serverPosition), port);
  client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client.SetAttribute ("PacketSize", UintegerValue (packetSize));
  uint16_t clientPosition = 0; //top left
  for (clientPosition = 0; clientPosition < size-1; clientPosition+=10)
     {
        apps = client.Install (nodes.Get (clientPosition));
     }
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (totalTime-0.1));
}

