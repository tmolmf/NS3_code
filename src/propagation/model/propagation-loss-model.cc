/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006,2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 * Contributions: Timo Bingmann <timo.bingmann@student.kit.edu>
 * Contributions: Tom Hewer <tomhewer@mac.com> for Two Ray Ground Model
 *                Pavel Boyko <boyko@iitp.ru> for matrix
 */

#include "propagation-loss-model.h"
#include "ns3/log.h"
#include "ns3/mobility-model.h"
#include "ns3/boolean.h"
#include "ns3/double.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
struct obtacle{
	//double under_x1,under_y1,under_z1,under_x2,under_y2,under_z2,under_x3,under_y3,under_z3,under_x4,under_y4,under_z4;
	double upper_x1,upper_y1,upper_z1,upper_x2,upper_y2,upper_z2,upper_x3,upper_y3,upper_z3,upper_x4,upper_y4,upper_z4;
};
*/

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PropagationLossModel");

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (PropagationLossModel);

TypeId 
PropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PropagationLossModel")
    .SetParent<Object> ()
  ;
  return tid;
}

// std::vector <obtacle> obstaclelist;

PropagationLossModel::PropagationLossModel ()
  : m_next (0)
{
//file load for obstacles data.
  std::cout<<"\n<!--Obstacles data loading at propagation constructor start-->"<<std::endl;

 ifstream inf("test.txt");



 vector <string> stringvector;
 string inStr;

 while(! inf.eof() ) {
  inf >> inStr;
  //inStr을 배열,vector,list등에 저장
  stringvector.push_back(inStr);
 }
 inf.close();


 while(!stringvector.empty())
 {
//	 std::cout << "<!--Flag1" << std::endl;
	 obtacle new_ob;
	 string current_str;
	 char tok_str;
	 string x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	 current_str = stringvector.back();

	 //std::cout << stringvector.back() << std::endl;
	 //while(current_str.find(tok_str, 0)!=string::npos)//??? 지금 당장은 좀 아니지??
	 {
		 tok_str = ':';
//		 std::cout << current_str<<std::endl;
		 x1 = current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 y1 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 z1 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 x2 = current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 y2 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 z2 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 x3 = current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 y3 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 z3 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 x4 = current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 y4 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 z4 =  current_str.substr(0, current_str.find(tok_str, 0));
		 current_str = current_str.substr(current_str.find(tok_str, 0)+1);
		 //x1 = current_str.substr(current_str.find(tok_str, 0));
		 //std::cout << "<!--Flag3" << std::endl;
/*
		 std::cout << x1 << " : ";
		 std::cout << y1 << " : ";
		 std::cout << z1 << " : ";
		 std::cout << x2 << " : ";
		 std::cout << y2 << " : ";
		 std::cout << z2 << " : ";
		 std::cout << x3 << " : ";
		 std::cout << y3 << " : ";
		 std::cout << z3 << " : ";
		 std::cout << x4 << " : ";
		 std::cout << y4 << " : ";
		 std::cout << z4 << std::endl;
*/
                        std::stringstream ss;

                        ss<<x1;
                        ss>>new_ob.upper_x1;
                        ss.clear();
                        ss<<y1;
                        ss>>new_ob.upper_y1;
                        ss.clear();
                        ss<<z1;
                        ss>>new_ob.upper_z1;
                        ss.clear();
                        ss<<x2;
                        ss>>new_ob.upper_x2;
                        ss.clear();
                        ss<<y2;
                        ss>>new_ob.upper_y2;
                        ss.clear();
                        ss<<z2;
                        ss>>new_ob.upper_z2;
                        ss.clear();
                        ss<<x3;
                        ss>>new_ob.upper_x3;
                        ss.clear();
                        ss<<y3;
                        ss>>new_ob.upper_y3;
                        ss.clear();
                        ss<<z3;
                        ss>>new_ob.upper_z3;
                        ss.clear();
                        ss<<x4;
                        ss>>new_ob.upper_x4;
                        ss.clear();
                        ss<<y4;
                        ss>>new_ob.upper_y4;
                        ss.clear();
                        ss<<z4;
                        ss>>new_ob.upper_z4;
                        ss.clear();
/*
		 new_ob.upper_x1=stod(x1);
		 new_ob.upper_y1=stod(y1);
		 new_ob.upper_z1=stod(z1);
		 new_ob.upper_x2=stod(x2);
		 new_ob.upper_y2=stod(y2);
		 new_ob.upper_z2=stod(z2);
		 new_ob.upper_x3=stod(x3);
		 new_ob.upper_y3=stod(y3);
		 new_ob.upper_z3=stod(z3);
		 new_ob.upper_x4=stod(x4);
		 new_ob.upper_y4=stod(y4);
		 new_ob.upper_z4=stod(z4);
*/
		 obstaclelist.push_back(new_ob);
	 }
	 stringvector.pop_back();
 }
/*
 while (!obstaclelist.empty())
 {
	 std::cout << obstaclelist.back().upper_x1 << ", " << obstaclelist.back().upper_y1 << ", " << obstaclelist.back().upper_z1 << ", "
		 << obstaclelist.back().upper_x2 << ", " << obstaclelist.back().upper_y2 << ", " << obstaclelist.back().upper_z2 << ", "
		 << obstaclelist.back().upper_x3 << ", " << obstaclelist.back().upper_y3 << ", " << obstaclelist.back().upper_z3 << ", "
		 << obstaclelist.back().upper_x4 << ", " << obstaclelist.back().upper_y4 << ", " << obstaclelist.back().upper_z4
		 << std::endl;
	 obstaclelist.pop_back();
 }
*/

  std::cout<<"<!--Obstacles data loading at propagation constructor finish-->\n"<<std::endl;
}

PropagationLossModel::~PropagationLossModel ()
{
}

void
PropagationLossModel::SetNext (Ptr<PropagationLossModel> next)
{
  m_next = next;
}

Ptr<PropagationLossModel>
PropagationLossModel::GetNext ()
{
  return m_next;
}

double
PropagationLossModel::CalcRxPower (double txPowerDbm,
                                   Ptr<MobilityModel> a,
                                   Ptr<MobilityModel> b) const
{
  double self = DoCalcRxPower (txPowerDbm, a, b);
  if (m_next != 0)
    {
      self = m_next->CalcRxPower (self, a, b);
    }
  return self;
}

int64_t
PropagationLossModel::AssignStreams (int64_t stream)
{
  int64_t currentStream = stream;
  currentStream += DoAssignStreams (stream);
  if (m_next != 0)
    {
      currentStream += m_next->AssignStreams (currentStream);
    }
  return (currentStream - stream);
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (RandomPropagationLossModel);

TypeId 
RandomPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::RandomPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<RandomPropagationLossModel> ()
    .AddAttribute ("Variable", "The random variable used to pick a loss everytime CalcRxPower is invoked.",
                   StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"),
                   MakePointerAccessor (&RandomPropagationLossModel::m_variable),
                   MakePointerChecker<RandomVariableStream> ())
  ;
  return tid;
}
RandomPropagationLossModel::RandomPropagationLossModel ()
  : PropagationLossModel ()
{
}

RandomPropagationLossModel::~RandomPropagationLossModel ()
{
}

double
RandomPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                           Ptr<MobilityModel> a,
                                           Ptr<MobilityModel> b) const
{
  double rxc = -m_variable->GetValue ();
  NS_LOG_DEBUG ("attenuation coefficent="<<rxc<<"Db");
  return txPowerDbm + rxc;
}

int64_t
RandomPropagationLossModel::DoAssignStreams (int64_t stream)
{
  m_variable->SetStream (stream);
  return 1;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (FriisPropagationLossModel);

TypeId 
FriisPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::FriisPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<FriisPropagationLossModel> ()
    .AddAttribute ("Frequency", 
                   "The carrier frequency (in Hz) at which propagation occurs  (default is 5.15 GHz).",
                   DoubleValue (5.150e9),
                   MakeDoubleAccessor (&FriisPropagationLossModel::SetFrequency,
                                       &FriisPropagationLossModel::GetFrequency),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("SystemLoss", "The system loss",
                   DoubleValue (1.0),
                   MakeDoubleAccessor (&FriisPropagationLossModel::m_systemLoss),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("MinLoss", 
                   "The minimum value (dB) of the total loss, used at short ranges. Note: ",
                   DoubleValue (0.0),
                   MakeDoubleAccessor (&FriisPropagationLossModel::SetMinLoss,
                                       &FriisPropagationLossModel::GetMinLoss),
                   MakeDoubleChecker<double> ())
  ;
  return tid;
}

FriisPropagationLossModel::FriisPropagationLossModel ()
{
}
void
FriisPropagationLossModel::SetSystemLoss (double systemLoss)
{
  m_systemLoss = systemLoss;
}
double
FriisPropagationLossModel::GetSystemLoss (void) const
{
  return m_systemLoss;
}
void
FriisPropagationLossModel::SetMinLoss (double minLoss)
{
  m_minLoss = minLoss;
}
double
FriisPropagationLossModel::GetMinLoss (void) const
{
  return m_minLoss;
}

void
FriisPropagationLossModel::SetFrequency (double frequency)
{
  m_frequency = frequency;
  static const double C = 299792458.0; // speed of light in vacuum
  m_lambda = C / frequency;
}

double
FriisPropagationLossModel::GetFrequency (void) const
{
  return m_frequency;
}

double
FriisPropagationLossModel::DbmToW (double dbm) const
{
  double mw = std::pow (10.0,dbm/10.0);
  return mw / 1000.0;
}

double
FriisPropagationLossModel::DbmFromW (double w) const
{
  double dbm = std::log10 (w * 1000.0) * 10.0;
  return dbm;
}

double 
FriisPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                          Ptr<MobilityModel> a,
                                          Ptr<MobilityModel> b) const
{
  /*
   * Friis free space equation:
   * where Pt, Gr, Gr and P are in Watt units
   * L is in meter units.
   *
   *    P     Gt * Gr * (lambda^2)
   *   --- = ---------------------
   *    Pt     (4 * pi * d)^2 * L
   *
   * Gt: tx gain (unit-less)
   * Gr: rx gain (unit-less)
   * Pt: tx power (W)
   * d: distance (m)
   * L: system loss
   * lambda: wavelength (m)
   *
   * Here, we ignore tx and rx gain and the input and output values 
   * are in dB or dBm:
   *
   *                           lambda^2
   * rx = tx +  10 log10 (-------------------)
   *                       (4 * pi * d)^2 * L
   *
   * rx: rx power (dB)
   * tx: tx power (dB)
   * d: distance (m)
   * L: system loss (unit-less)
   * lambda: wavelength (m)
   */
  double distance = a->GetDistanceFrom (b);
  if (distance < 3*m_lambda)
    {
      NS_LOG_WARN ("distance not within the far field region => inaccurate propagation loss value");
    }
  if (distance <= 0)
    {
      return txPowerDbm - m_minLoss;
    }
  double numerator = m_lambda * m_lambda;
  double denominator = 16 * M_PI * M_PI * distance * distance * m_systemLoss;
  double lossDb = -10 * log10 (numerator / denominator);
  NS_LOG_DEBUG ("distance=" << distance<< "m, loss=" << lossDb <<"dB");
  return txPowerDbm - std::max (lossDb, m_minLoss);
}

int64_t
FriisPropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //
// -- Two-Ray Ground Model ported from NS-2 -- tomhewer@mac.com -- Nov09 //

NS_OBJECT_ENSURE_REGISTERED (TwoRayGroundPropagationLossModel);

TypeId 
TwoRayGroundPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TwoRayGroundPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<TwoRayGroundPropagationLossModel> ()
    .AddAttribute ("Frequency", 
                   "The carrier frequency (in Hz) at which propagation occurs  (default is 5.15 GHz).",
                   DoubleValue (5.150e9),
                   MakeDoubleAccessor (&TwoRayGroundPropagationLossModel::SetFrequency,
                                       &TwoRayGroundPropagationLossModel::GetFrequency),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("SystemLoss", "The system loss",
                   DoubleValue (1.0),
                   MakeDoubleAccessor (&TwoRayGroundPropagationLossModel::m_systemLoss),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("MinDistance",
                   "The distance under which the propagation model refuses to give results (m)",
                   DoubleValue (0.5),
                   MakeDoubleAccessor (&TwoRayGroundPropagationLossModel::SetMinDistance,
                                       &TwoRayGroundPropagationLossModel::GetMinDistance),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("HeightAboveZ",
                   "The height of the antenna (m) above the node's Z coordinate",
                   DoubleValue (0),
                   MakeDoubleAccessor (&TwoRayGroundPropagationLossModel::m_heightAboveZ),
                   MakeDoubleChecker<double> ())
  ;
  return tid;
}

TwoRayGroundPropagationLossModel::TwoRayGroundPropagationLossModel ()
{
}
void
TwoRayGroundPropagationLossModel::SetSystemLoss (double systemLoss)
{
  m_systemLoss = systemLoss;
}
double
TwoRayGroundPropagationLossModel::GetSystemLoss (void) const
{
  return m_systemLoss;
}
void
TwoRayGroundPropagationLossModel::SetMinDistance (double minDistance)
{
  m_minDistance = minDistance;
}
double
TwoRayGroundPropagationLossModel::GetMinDistance (void) const
{
  return m_minDistance;
}
void
TwoRayGroundPropagationLossModel::SetHeightAboveZ (double heightAboveZ)
{
  m_heightAboveZ = heightAboveZ;
}

void
TwoRayGroundPropagationLossModel::SetFrequency (double frequency)
{
  m_frequency = frequency;
  static const double C = 299792458.0; // speed of light in vacuum
  m_lambda = C / frequency;
}

double
TwoRayGroundPropagationLossModel::GetFrequency (void) const
{
  return m_frequency;
}

double 
TwoRayGroundPropagationLossModel::DbmToW (double dbm) const
{
  double mw = std::pow (10.0,dbm / 10.0);
  return mw / 1000.0;
}

double
TwoRayGroundPropagationLossModel::DbmFromW (double w) const
{
  double dbm = std::log10 (w * 1000.0) * 10.0;
  return dbm;
}

double 
TwoRayGroundPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                                 Ptr<MobilityModel> a,
                                                 Ptr<MobilityModel> b) const
{
  /*
   * Two-Ray Ground equation:
   *
   * where Pt, Gt and Gr are in dBm units
   * L, Ht and Hr are in meter units.
   *
   *   Pr      Gt * Gr * (Ht^2 * Hr^2)
   *   -- =  (-------------------------)
   *   Pt            d^4 * L
   *
   * Gt: tx gain (unit-less)
   * Gr: rx gain (unit-less)
   * Pt: tx power (dBm)
   * d: distance (m)
   * L: system loss
   * Ht: Tx antenna height (m)
   * Hr: Rx antenna height (m)
   * lambda: wavelength (m)
   *
   * As with the Friis model we ignore tx and rx gain and output values
   * are in dB or dBm
   *
   *                      (Ht * Ht) * (Hr * Hr)
   * rx = tx + 10 log10 (-----------------------)
   *                      (d * d * d * d) * L
   */
  double distance = a->GetDistanceFrom (b);
  if (distance <= m_minDistance)
    {
std::cout<<"<!--txPowerDbm distance short : "<<txPowerDbm<<"-->"<<std::endl;
      return txPowerDbm;
    }


 double u[5], v[5];
 double d_x1, d_y1, d_z1, d_x2, d_y2, d_z2, d_x3, d_y3, d_z3, d_x4, d_y4, d_z4;
        int los_onoff=1;

	d_x1=a->GetPosition ().x;
	d_y1=a->GetPosition ().y;
	d_z1=a->GetPosition ().z;
	d_x2=b->GetPosition ().x;
	d_y2=b->GetPosition ().y;
	d_z2=b->GetPosition ().z;

//매번 모든 장애물 4점 정보를 출력하도록 작성되어 있으나, 이 정보를 이용해서 장애물의 영향을 판별하는 공식으로 바꾸어야 함.
 for(unsigned int i=0;i<obstaclelist.size();i++)
 {
/*
	 std::cout << obstaclelist.at(i).upper_x1 << ", " << obstaclelist.at(i).upper_y1 << ", " << obstaclelist.at(i).upper_z1 << ", "
		 << obstaclelist.at(i).upper_x2 << ", " << obstaclelist.at(i).upper_y2 << ", " << obstaclelist.at(i).upper_z2 << ", "
		 << obstaclelist.at(i).upper_x3 << ", " << obstaclelist.at(i).upper_y3 << ", " << obstaclelist.at(i).upper_z3 << ", "
		 << obstaclelist.at(i).upper_x4 << ", " << obstaclelist.at(i).upper_y4 << ", " << obstaclelist.at(i).upper_z4
		 << std::endl;
*/


	d_x3=obstaclelist.at(i).upper_x1;
	d_y3=obstaclelist.at(i).upper_y1;
	d_z3=obstaclelist.at(i).upper_z1;
	d_x4=obstaclelist.at(i).upper_x2;
	d_y4=obstaclelist.at(i).upper_y2;
	d_z4=obstaclelist.at(i).upper_z2;

	u[0] = ((d_x4-d_x3)*(d_y1-d_y3)-(d_y4-d_y3)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));
	v[0] = ((d_x2-d_x1)*(d_y1-d_y3)-(d_y2-d_y1)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));
		
        d_x3=obstaclelist.at(i).upper_x2;
	d_y3=obstaclelist.at(i).upper_y2;
	d_z3=obstaclelist.at(i).upper_z2;
	d_x4=obstaclelist.at(i).upper_x4;
	d_y4=obstaclelist.at(i).upper_y4;
	d_z4=obstaclelist.at(i).upper_z4;

	u[1] = ((d_x4-d_x3)*(d_y1-d_y3)-(d_y4-d_y3)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));
	v[1] = ((d_x2-d_x1)*(d_y1-d_y3)-(d_y2-d_y1)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));
	
	d_x3=obstaclelist.at(i).upper_x3;
	d_y3=obstaclelist.at(i).upper_y3;
	d_z3=obstaclelist.at(i).upper_z3;
	d_x4=obstaclelist.at(i).upper_x4;
	d_y4=obstaclelist.at(i).upper_y4;
	d_z4=obstaclelist.at(i).upper_z4;

	u[2] = ((d_x4-d_x3)*(d_y1-d_y3)-(d_y4-d_y3)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));
	v[2] = ((d_x2-d_x1)*(d_y1-d_y3)-(d_y2-d_y1)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));

	d_x3=obstaclelist.at(i).upper_x2;
	d_y3=obstaclelist.at(i).upper_y2;
	d_z3=obstaclelist.at(i).upper_z2;
	d_x4=obstaclelist.at(i).upper_x1;
	d_y4=obstaclelist.at(i).upper_y1;
	d_z4=obstaclelist.at(i).upper_z1;

	u[3] = ((d_x4-d_x3)*(d_y1-d_y3)-(d_y4-d_y3)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));
	v[3] = ((d_x2-d_x1)*(d_y1-d_y3)-(d_y2-d_y1)*(d_x1-d_x3)) / ((d_x2-d_x1)*(d_y4-d_y3)-(d_x4-d_x3)*(d_y2-d_y1));

        v[4] = d_z1+d_z2+d_z3+d_z4;


	 for(int i=0;i<4;i++)
		if(u[i]>0&&u[i]<1&&v[i]>0&&v[i]<1)
                        los_onoff=0;
 }

  // Set the height of the Tx and Rx antennae
  double txAntHeight = a->GetPosition ().z + m_heightAboveZ;// +((a->GetPosition ().x)-(a->GetPosition ().x/10));
  double rxAntHeight = b->GetPosition ().z + m_heightAboveZ;// +((b->GetPosition ().x)-(b->GetPosition ().x/10));

  // Calculate a crossover distance, under which we use Friis
  /*
   * 
   * dCross = (4 * pi * Ht * Hr) / lambda
   *
   */

  double dCross = (4 * M_PI * txAntHeight * rxAntHeight) / m_lambda;
  double tmp = 0;
  if (false)//distance <= dCross)
    {
      // We use Friis
      double numerator = m_lambda * m_lambda;
      tmp = M_PI * distance;
      double denominator = 16 * tmp * tmp * m_systemLoss;
      double pr = 10 * std::log10 (numerator / denominator);
      NS_LOG_DEBUG ("Receiver within crossover (" << dCross << "m) for Two_ray path; using Friis");
      NS_LOG_DEBUG ("distance=" << distance << "m, attenuation coefficient=" << pr << "dB");
//std::cout<<"<!--txPowerDbm Friis : "<<txPowerDbm + pr<<"-->"<<std::endl;
      return txPowerDbm + pr;
    }
  else   // Use Two-Ray Pathloss
    {
      tmp = txAntHeight * rxAntHeight;
      double rayNumerator = tmp * tmp;
      tmp = distance * distance;
      double rayDenominator = tmp * tmp * m_systemLoss;
      double rayPr = 10 * std::log10 (rayNumerator / rayDenominator);
        if(los_onoff==0)
                rayPr-=100;
      NS_LOG_DEBUG ("distance=" << distance << "m, attenuation coefficient=" << rayPr << "dB");
std::cout<<"<!--txPowerDbm Two-Ray : "<<txPowerDbm + rayPr<<"-->"<<"\nSender : "<<a->GetPosition ().x<<" : "<<a->GetPosition ().y<<" Receiver : "<<b->GetPosition ().x<<" : "<<b->GetPosition ().y<<" LOS onoff : "<< los_onoff <<std::endl;//add



	d_x1=a->GetPosition ().x;
	d_y1=a->GetPosition ().y;
	d_z1=a->GetPosition ().z;
	d_x2=b->GetPosition ().x;
	d_y2=b->GetPosition ().y;
	d_z2=b->GetPosition ().z;

      return txPowerDbm + rayPr;

    }
}

int64_t
TwoRayGroundPropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (LogDistancePropagationLossModel);

TypeId
LogDistancePropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LogDistancePropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<LogDistancePropagationLossModel> ()
    .AddAttribute ("Exponent",
                   "The exponent of the Path Loss propagation model",
                   DoubleValue (3.0),
                   MakeDoubleAccessor (&LogDistancePropagationLossModel::m_exponent),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ReferenceDistance",
                   "The distance at which the reference loss is calculated (m)",
                   DoubleValue (1.0),
                   MakeDoubleAccessor (&LogDistancePropagationLossModel::m_referenceDistance),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ReferenceLoss",
                   "The reference loss at reference distance (dB). (Default is Friis at 1m with 5.15 GHz)",
                   DoubleValue (46.6777),
                   MakeDoubleAccessor (&LogDistancePropagationLossModel::m_referenceLoss),
                   MakeDoubleChecker<double> ())
  ;
  return tid;

}

LogDistancePropagationLossModel::LogDistancePropagationLossModel ()
{
}

void
LogDistancePropagationLossModel::SetPathLossExponent (double n)
{
  m_exponent = n;
}
void
LogDistancePropagationLossModel::SetReference (double referenceDistance, double referenceLoss)
{
  m_referenceDistance = referenceDistance;
  m_referenceLoss = referenceLoss;
}
double
LogDistancePropagationLossModel::GetPathLossExponent (void) const
{
  return m_exponent;
}

double
LogDistancePropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                                Ptr<MobilityModel> a,
                                                Ptr<MobilityModel> b) const
{
  double distance = a->GetDistanceFrom (b);
  if (distance <= m_referenceDistance)
    {
      return txPowerDbm;
    }
  /**
   * The formula is:
   * rx = 10 * log (Pr0(tx)) - n * 10 * log (d/d0)
   *
   * Pr0: rx power at reference distance d0 (W)
   * d0: reference distance: 1.0 (m)
   * d: distance (m)
   * tx: tx power (dB)
   * rx: dB
   *
   * Which, in our case is:
   *
   * rx = rx0(tx) - 10 * n * log (d/d0)
   */
  double pathLossDb = 10 * m_exponent * std::log10 (distance / m_referenceDistance);
  double rxc = -m_referenceLoss - pathLossDb;
  NS_LOG_DEBUG ("distance="<<distance<<"m, reference-attenuation="<< -m_referenceLoss<<"dB, "<<
                "attenuation coefficient="<<rxc<<"db");
  return txPowerDbm + rxc;
}

int64_t
LogDistancePropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (ThreeLogDistancePropagationLossModel);

TypeId
ThreeLogDistancePropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ThreeLogDistancePropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<ThreeLogDistancePropagationLossModel> ()
    .AddAttribute ("Distance0",
                   "Beginning of the first (near) distance field",
                   DoubleValue (1.0),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_distance0),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("Distance1",
                   "Beginning of the second (middle) distance field.",
                   DoubleValue (200.0),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_distance1),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("Distance2",
                   "Beginning of the third (far) distance field.",
                   DoubleValue (500.0),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_distance2),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("Exponent0",
                   "The exponent for the first field.",
                   DoubleValue (1.9),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_exponent0),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("Exponent1",
                   "The exponent for the second field.",
                   DoubleValue (3.8),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_exponent1),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("Exponent2",
                   "The exponent for the third field.",
                   DoubleValue (3.8),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_exponent2),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ReferenceLoss",
                   "The reference loss at distance d0 (dB). (Default is Friis at 1m with 5.15 GHz)",
                   DoubleValue (46.6777),
                   MakeDoubleAccessor (&ThreeLogDistancePropagationLossModel::m_referenceLoss),
                   MakeDoubleChecker<double> ())
  ;
  return tid;

}

ThreeLogDistancePropagationLossModel::ThreeLogDistancePropagationLossModel ()
{
}

double 
ThreeLogDistancePropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                                     Ptr<MobilityModel> a,
                                                     Ptr<MobilityModel> b) const
{
  double distance = a->GetDistanceFrom (b);
  NS_ASSERT (distance >= 0);

  // See doxygen comments for the formula and explanation

  double pathLossDb;

  if (distance < m_distance0)
    {
      pathLossDb = 0;
    }
  else if (distance < m_distance1)
    {
      pathLossDb = m_referenceLoss
        + 10 * m_exponent0 * std::log10 (distance / m_distance0);
    }
  else if (distance < m_distance2)
    {
      pathLossDb = m_referenceLoss
        + 10 * m_exponent0 * std::log10 (m_distance1 / m_distance0)
        + 10 * m_exponent1 * std::log10 (distance / m_distance1);
    }
  else
    {
      pathLossDb = m_referenceLoss
        + 10 * m_exponent0 * std::log10 (m_distance1 / m_distance0)
        + 10 * m_exponent1 * std::log10 (m_distance2 / m_distance1)
        + 10 * m_exponent2 * std::log10 (distance / m_distance2);
    }

  NS_LOG_DEBUG ("ThreeLogDistance distance=" << distance << "m, " <<
                "attenuation=" << pathLossDb << "dB");

  return txPowerDbm - pathLossDb;
}

int64_t
ThreeLogDistancePropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (NakagamiPropagationLossModel);

TypeId
NakagamiPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::NakagamiPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<NakagamiPropagationLossModel> ()
    .AddAttribute ("Distance1",
                   "Beginning of the second distance field. Default is 80m.",
                   DoubleValue (80.0),
                   MakeDoubleAccessor (&NakagamiPropagationLossModel::m_distance1),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("Distance2",
                   "Beginning of the third distance field. Default is 200m.",
                   DoubleValue (200.0),
                   MakeDoubleAccessor (&NakagamiPropagationLossModel::m_distance2),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("m0",
                   "m0 for distances smaller than Distance1. Default is 1.5.",
                   DoubleValue (1.5),
                   MakeDoubleAccessor (&NakagamiPropagationLossModel::m_m0),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("m1",
                   "m1 for distances smaller than Distance2. Default is 0.75.",
                   DoubleValue (0.75),
                   MakeDoubleAccessor (&NakagamiPropagationLossModel::m_m1),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("m2",
                   "m2 for distances greater than Distance2. Default is 0.75.",
                   DoubleValue (0.75),
                   MakeDoubleAccessor (&NakagamiPropagationLossModel::m_m2),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ErlangRv",
                   "Access to the underlying ErlangRandomVariable",
                   StringValue ("ns3::ErlangRandomVariable"),
                   MakePointerAccessor (&NakagamiPropagationLossModel::m_erlangRandomVariable),
                   MakePointerChecker<ErlangRandomVariable> ())
    .AddAttribute ("GammaRv",
                   "Access to the underlying GammaRandomVariable",
                   StringValue ("ns3::GammaRandomVariable"),
                   MakePointerAccessor (&NakagamiPropagationLossModel::m_gammaRandomVariable),
                   MakePointerChecker<GammaRandomVariable> ());
  ;
  return tid;

}

NakagamiPropagationLossModel::NakagamiPropagationLossModel ()
{
}

double
NakagamiPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                             Ptr<MobilityModel> a,
                                             Ptr<MobilityModel> b) const
{
  // select m parameter

  double distance = a->GetDistanceFrom (b);
  NS_ASSERT (distance >= 0);

  double m;
  if (distance < m_distance1)
    {
      m = m_m0;
    }
  else if (distance < m_distance2)
    {
      m = m_m1;
    }
  else
    {
      m = m_m2;
    }

  // the current power unit is dBm, but Watt is put into the Nakagami /
  // Rayleigh distribution.
  double powerW = std::pow (10, (txPowerDbm - 30) / 10);

  double resultPowerW;

  // switch between Erlang- and Gamma distributions: this is only for
  // speed. (Gamma is equal to Erlang for any positive integer m.)
  unsigned int int_m = static_cast<unsigned int>(std::floor (m));

  if (int_m == m)
    {
      resultPowerW = m_erlangRandomVariable->GetValue (int_m, powerW / m);
    }
  else
    {
      resultPowerW = m_gammaRandomVariable->GetValue (m, powerW / m);
    }

  double resultPowerDbm = 10 * std::log10 (resultPowerW) + 30;

  NS_LOG_DEBUG ("Nakagami distance=" << distance << "m, " <<
                "power=" << powerW <<"W, " <<
                "resultPower=" << resultPowerW << "W=" << resultPowerDbm << "dBm");

  return resultPowerDbm;
}

int64_t
NakagamiPropagationLossModel::DoAssignStreams (int64_t stream)
{
  m_erlangRandomVariable->SetStream (stream);
  m_gammaRandomVariable->SetStream (stream + 1);
  return 2;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (FixedRssLossModel);

TypeId 
FixedRssLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::FixedRssLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<FixedRssLossModel> ()
    .AddAttribute ("Rss", "The fixed receiver Rss.",
                   DoubleValue (-150.0),
                   MakeDoubleAccessor (&FixedRssLossModel::m_rss),
                   MakeDoubleChecker<double> ())
  ;
  return tid;
}
FixedRssLossModel::FixedRssLossModel ()
  : PropagationLossModel ()
{
}

FixedRssLossModel::~FixedRssLossModel ()
{
}

void
FixedRssLossModel::SetRss (double rss)
{
  m_rss = rss;
}

double
FixedRssLossModel::DoCalcRxPower (double txPowerDbm,
                                  Ptr<MobilityModel> a,
                                  Ptr<MobilityModel> b) const
{
  return m_rss;
}

int64_t
FixedRssLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (MatrixPropagationLossModel);

TypeId 
MatrixPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MatrixPropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<MatrixPropagationLossModel> ()
    .AddAttribute ("DefaultLoss", "The default value for propagation loss, dB.",
                   DoubleValue (std::numeric_limits<double>::max ()),
                   MakeDoubleAccessor (&MatrixPropagationLossModel::m_default),
                   MakeDoubleChecker<double> ())
  ;
  return tid;
}

MatrixPropagationLossModel::MatrixPropagationLossModel ()
  : PropagationLossModel (), m_default (std::numeric_limits<double>::max ())
{
}

MatrixPropagationLossModel::~MatrixPropagationLossModel ()
{
}

void 
MatrixPropagationLossModel::SetDefaultLoss (double loss)
{
  m_default = loss;
}

void
MatrixPropagationLossModel::SetLoss (Ptr<MobilityModel> ma, Ptr<MobilityModel> mb, double loss, bool symmetric)
{
  NS_ASSERT (ma != 0 && mb != 0);

  MobilityPair p = std::make_pair (ma, mb);
  std::map<MobilityPair, double>::iterator i = m_loss.find (p);

  if (i == m_loss.end ())
    {
      m_loss.insert (std::make_pair (p, loss));
    }
  else
    {
      i->second = loss;
    }

  if (symmetric)
    {
      SetLoss (mb, ma, loss, false);
    }
}

double 
MatrixPropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                           Ptr<MobilityModel> a,
                                           Ptr<MobilityModel> b) const
{
  std::map<MobilityPair, double>::const_iterator i = m_loss.find (std::make_pair (a, b));

  if (i != m_loss.end ())
    {
      return txPowerDbm - i->second;
    }
  else
    {
      return txPowerDbm - m_default;
    }
}

int64_t
MatrixPropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //

NS_OBJECT_ENSURE_REGISTERED (RangePropagationLossModel);

TypeId
RangePropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::RangePropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<RangePropagationLossModel> ()
    .AddAttribute ("MaxRange",
                   "Maximum Transmission Range (meters)",
                   DoubleValue (250),
                   MakeDoubleAccessor (&RangePropagationLossModel::m_range),
                   MakeDoubleChecker<double> ())
  ;
  return tid;
}

RangePropagationLossModel::RangePropagationLossModel ()
{
}

double
RangePropagationLossModel::DoCalcRxPower (double txPowerDbm,
                                          Ptr<MobilityModel> a,
                                          Ptr<MobilityModel> b) const
{
  double distance = a->GetDistanceFrom (b);
  if (distance <= m_range)
    {
      return txPowerDbm;
    }
  else
    {
      return -1000;
    }
}

int64_t
RangePropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

// ------------------------------------------------------------------------- //

} // namespace ns3
