
/**************************************************************************/
/* Object Dictionary for the node Linux_slave, default node_id : 0x01       */
/*                                                                        */
/* Computed by "makeobjetdict.php"                                        */
/**************************************************************************/
/* Computed by strComputed */

/*********************************************************                   
 *                                                       *
 *             Master/slave CANopen Library              *

 *********************************************************
           File : objdict.c
 *-------------------------------------------------------*
 * This is where you defined the dictionary of your      *
 *  application                                          *      
 *                                                       *
 *********************************************************/
 /* Computed by strEntete */

//#define DEBUG_CAN

#include <stddef.h>
#include <global.h>
#include INCLUDE_H

#include "def.h"
#include "pdo.h"
#include "sdo.h"
#include "sync.h"
#include "objdictdef.h"
#include "nmtSlave.h"
#include "lifegrd.h"

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* Computed by strNode */
/* node_id default value. 
   You should always overwrite this by using the function setNodeId(UNS8 nodeId) in your C code.
*/
#define NODE_ID 0x02

/**************************************************************************/
/* Declaration of the mapped variables                                    */
/**************************************************************************/
/* Computed by strDeclareMapVar */
UNS8 seconds;		// Mapped at index 0x2000, subindex 0x1
UNS8 minutes;		// Mapped at index 0x2000, subindex 0x2
UNS8 hours;			// Mapped at index 0x2000, subindex 0x3
UNS16 day;			// Mapped at index 0x2000, subindex 0x4
//UNS32 canopenErrNB;	// Mapped at index 0x6000, subindex 0x0
//UNS32 canopenErrVAL;// Mapped at index 0x6001, subindex 0x0

//*****************************************************************************/
/* Computed by strStartDico */

/* Array of message processing information */
/* Should not be modified */
const proceed_info proceed_infos[] = 
{
  {NMT,			"NMT",	        proceedNMTstateChange},		//0
  {SYNC,        "SYNC",         proceedSYNC},				//1
  {TIME_STAMP,	"TIME_STAMP",	0},							//2
  {PDO1tx,		"PDO1tx",       proceedPDO},				//3
  {PDO1rx,		"PDO1rx",		proceedPDO},				//4
  {PDO2tx,		"PDO2tx",		proceedPDO},				//5	
  {PDO2rx,		"PDO2rx",		proceedPDO},				//6
  {PDO3tx,		"PDO3tx",		proceedPDO},				//7
  {PDO3rx,		"PDO3rx",		proceedPDO},				//8
  {PDO4tx,		"PDO4tx",		proceedPDO},				//9
  {PDO4rx,		"PDO4rx",		proceedPDO},				//10
  {SDOtx,		"SDOtx",		proceedSDO},				//11
  {SDOrx,		"SDOrx",        proceedSDO},				//12
  {0xD,			"Unknown",		0},							//13
  {NODE_GUARD,	"NODE GUARD",   proceedNMTerror},			//14
  {0xF,			"Unknown",		0},							//15
  {0x10,		"PDO5",			proceedPDO},				//16
  {0x11,		"PDO6",			proceedPDO},				//17
  {0x12,		"PDO7",			proceedPDO},				//18
  {0x13,		"PDO8",			proceedPDO},				//19
  {0x14,		"PDO9",			proceedPDO},				//20
  {0x15,		"PDO10",		proceedPDO},				//21
  {0x16,		"PDO11",		proceedPDO},				//22
  {0x17,		"PDO12",		proceedPDO},				//23
  {0x18,		"PDO13",		proceedPDO},				//24
  {0x19,		"PDO14",		proceedPDO},				//25
 
  {0x1A,		"PDO15",		proceedPDO}					//26
  //{0x1B,			"Unknown",		0},							//27
  //{0x1C,			"Unknown",		0},							//28
  //{0x1D,			"Unknown",		0},							//29
  //{0x1E,			"Unknown",		0},							//30
  //{0x1F,			"Unknown",		0},							//31
  
  //{0x20,			"Unknown",		0},							//32
  //{0x21,			"Unknown",		0},							//33
  //{0x22,			"Unknown",		0},							//34
  //{0x23,			"Unknown",		0},							//35
  //{0x24,			"Unknown",		0},							//36
  //{0x25,			"Unknown",		0},							//37
  //{0x26,			"Unknown",		0},							//38
  //{0x27,			"Unknown",		0},							//39
  //{0x28,			"Unknown",		0},							//40
  //{0x29,			"Unknown",		0},							//41
  //{0x2A,			"Unknown",		0},							//42
  //{0x2B,			"Unknown",		0},							//43
  //{0x2C,			"Unknown",		0},							//44
  //{0x2D,			"Unknown",		0},							//45
  //{0x2E,			"Unknown",		0},							//46
  //{0x2F,			"Unknown",		0},							//47

  //{0x30,			"Unknown",		0},							//48
  //{0x31,			"Unknown",		0},							//49
  //{0x32,			"Unknown",		0},							//50
  //{0x33,			"Unknown",		0},							//51
  //{0x34,			"Unknown",		0},							//52
  //{0x35,			"Unknown",		0},							//53
  //{0x36,			"Unknown",		0},							//54
  //{0x37,			"Unknown",		0},							//55
  //{0x38,			"Unknown",		0},							//56
  //{0x39,			"Unknown",		0},							//57
  //{0x3A,			"Unknown",		0},							//58
  //{0x3B,			"Unknown",		0},							//59
  //{0x3C,			"Unknown",		0},							//60
  //{0x3D,			"Unknown",		0},							//61
  //{0x3E,			"Unknown",		0},							//62
  //{0x3F,			"Unknown",		0},							//63
};
const UNS8 Num_Proc_Max=sizeof(proceed_infos)/sizeof(proceed_info)-1;



//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//
//                       OBJECT DICTIONARY
//                   
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// Make your change, depending of your application
 
/** index 1000h: device type. You have to change the value below, so
 *  it fits your canopen-slave-module
 */
/* Not used, so, should not be modified */
#define OBJNAME devicetype
const UNS32 OBJNAME = DEVICE_TYPE;

const subindex Index1000[] =
{
  { RO, uint32, sizeof(UNS32), (void*)&OBJNAME }
};
#undef OBJNAME

/** index 1001: error register. Change the entries to fit your application
 */
/* Not used, so, should not be modified */
#define OBJNAME errorRegister
/*const*/ UNS8 OBJNAME = 0x0;
const subindex Index1001[] =
{
  { RO, uint8, sizeof(UNS8), (void*)&OBJNAME }
};
#undef OBJNAME

/** index 1005: COB_ID SYNC
*/
/* Should not be modified */
#define OBJNAME CobIdSync
UNS32 OBJNAME = 0x40000080; // bit 30 = 1 : device can generate a SYNC message
const subindex Index1005[] =
{
  { RW, uint32, sizeof(UNS32), (void*)&OBJNAME }
};
#undef OBJNAME

/** index 1006: SYNC period
*/

#define OBJNAME SyncPeriod
// For producing the SYNC signal every n micro-seconds.
// Put O to not producing SYNC
/*const*/ UNS32 OBJNAME = 0x0; /* Default 0 to not produce SYNC */
const subindex Index1006[] =
{
  { RW, uint32, sizeof(UNS32), (void*)&OBJNAME }
};
#undef OBJNAME
//==================================================================================================
/** index 1008: _азва-и_ устрRcства*/

#define OBJNAME Device_Name
const char OBJNAME[] = NAME_MODUL;

const subindex Index1008[] =
{
  { RO, visible_string, sizeof(OBJNAME), (void*)&OBJNAME }
};
#undef OBJNAME

/** index 100A: '_рси   рR_раммы*/
#define OBJNAME SoftwareVer
//const char OBJNAME[] = { __TIME__" " __DATE__}; 
const subindex Index100A[] =
{
  { RO, visible_string, sizeof(OBJNAME), (void*)&OBJNAME }
};
#undef OBJNAME

//=================================================================================================
/** index 100B : The node Id number
 */
/* Value may be modified */
#define OBJNAME bDeviceNodeId
UNS8 bDeviceNodeId = NODE_ID;
subindex Index100B[] =
{
  { RW, uint8, sizeof(UNS8), (void*) &OBJNAME }
};
#undef OBJNAME

/**************************************************************************/
/* HeartBeat consumers : The nodes which can send a heartbeat             */
/**************************************************************************/
/* Computed by strHeartBeatConsumers */
//static  UNS32 HBConsumerTimeArray[] = {0x00000000}; // Format 0x00NNTTTT (N=Node T=time in ms)

//static  UNS8 HBConsumerCount = 1; // 1 nodes could send me their heartbeat.
/*
subindex Index1016[] = {
  { RO, uint8, sizeof(UNS8), (void*)&HBConsumerCount },
  { RW, uint32, sizeof(UNS32), (void*)&HBConsumerTimeArray[0] }};

/**************************************************************************/
/* The node produce an heartbeat                                          */
/**************************************************************************/
/* Computed by strHeartBeatProducer */
/* Every HBProducerTime, the node sends its heartbeat */
static UNS16 HBProducerTime = 0;  /* in ms. If 0 : not activated */ 
const subindex Index1017[] =
{
	{ RW, uint16, sizeof(UNS16), &HBProducerTime }
};

/**************************************************************************/
/* Next to 0x1018                                                 */
/**************************************************************************/
/* Computed by strVaria1 */
/** index 1018: identify object. Adjust the entries for your node/company
 */
/* Values can be modified */
#define OBJNAME theIdentity
const s_identity OBJNAME =
{
  6,       		// number of supported entries
  0x1234,  		// Vendor-ID (given by the can-cia)
  0x5678,  		// Product Code
  0x1364,  		// Revision number
  0x79641234,  	// serial number
} ;

UNS16	ID_PROG_FLASH;
/* Should not be modified */
const subindex Index1018[] =
{
  { RO, uint8,  sizeof(UNS8),  (void*)&OBJNAME.count },
  { RO, uint32, sizeof(UNS32), (void*)&OBJNAME.vendor_id},
  { RO, uint32, sizeof(UNS32), (void*)&OBJNAME.product_code},
  { RO, uint32, sizeof(UNS32), (void*)&OBJNAME.revision_number},
  { RO, uint32, sizeof(UNS32), (void*)&OBJNAME.serial_number},
  { RW, uint16, sizeof(UNS16), (void*)&ID_PROG_FLASH}
};
#undef OBJNAME

/** now the communication profile entries are grouped together, so they
 *  can be accessed in a standardised manner. This could be memory-optimized
 *  if the empty entries wouldn't be added, but then the communication profile
 *  area must be accessed different (see objacces.c file)
 */
/* Should not be modified */
__far const indextable CommunicationProfileArea[] =
{
  DeclareIndexTableEntry(Index1000), // creates a line like: { Index1000, 1 },
  DeclareIndexTableEntry(Index1001),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index1005),
  DeclareIndexTableEntry(Index1006),
  { NULL, 0 },
  DeclareIndexTableEntry(Index1008),
  { NULL, 0 },
  DeclareIndexTableEntry(Index100A),
  DeclareIndexTableEntry(Index100B),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },//DeclareIndexTableEntry(Index1016),
  DeclareIndexTableEntry(Index1017),
  DeclareIndexTableEntry(Index1018),
};

/**************************************************************************/
/* The SDO Server parameters                                              */
/**************************************************************************/
/* Computed by strSdoServer */
/* BEWARE You cannot define more than one SDO server */


#define INDEX_LAST_SDO_SERVER           0x1200
#define DEF_MAX_COUNT_OF_SDO_SERVER     INDEX_LAST_SDO_SERVER - 0x11FF

/* The values should not be modified here, but can be changed at runtime */
#define OBJNAME serverSDO1
static s_sdo_parameter OBJNAME = 
{ 3,                   // Number of entries. Always 3 for the SDO	       
  0x600 + NODE_ID,     // The cob_id transmited in CAN msg to the server     
  0x580 + NODE_ID,     // The cob_id received in CAN msg from the server  
  NODE_ID              // The node id of the client. Should not be modified 
};
static subindex Index1200[] =
{
  { RO, uint8,  sizeof( UNS8 ), (void*)&OBJNAME.count },
  { RO, uint32, sizeof( UNS32), (void*)&OBJNAME.cob_id_client },
  { RO, uint32, sizeof( UNS32), (void*)&OBJNAME.cob_id_server },
  { RW, uint8,  sizeof( UNS8),  (void*)&OBJNAME.node_id }
};
#undef OBJNAME

/** Create the server SDO Parameter area.
 */
/* Should not be modified */
__far const indextable serverSDOParameter[] =
{
  DeclareIndexTableEntry(Index1200)
};

/**************************************************************************/
/* The SDO(s) clients                                                     */
/**************************************************************************/
/* Computed by strSdoClients */
/* For a slave node, declare only one SDO client to send data to the master */
/* The master node must have one SDO client for each slave */
#define INDEX_LAST_SDO_CLIENT           0x1280
#define DEF_MAX_COUNT_OF_SDO_CLIENT     1

#define _CREATE_SDO_CLIENT_(SDONUM) \
static  s_sdo_parameter clientSDO ## SDONUM = \
{ 3,    /* Number of entries. Always 3 for the SDO*/\
0x580,  /* The cob_id transmited in CAN msg to the server*/\
0x600,  /* The cob_id received in CAN msg from the server*/\
0x00    /* The node id of the client. Should not be modified */\
};\
static  subindex Index ## SDONUM  [] =\
{\
	{ RO, uint8, sizeof( UNS8 ), (void*)&clientSDO ## SDONUM.count },\
	{ RO, uint32, sizeof( UNS32), (void*)&clientSDO ## SDONUM.cob_id_client },\
	{ RO, uint32, sizeof( UNS32), (void*)&clientSDO ## SDONUM.cob_id_server },\
	{ RO, uint8, sizeof( UNS8), (void*)&clientSDO ## SDONUM.node_id }\
};

_CREATE_SDO_CLIENT_(1280)

/* Create the client SDO Parameter area. */
__far const indextable   clientSDOParameter[] =
{
  DeclareIndexTableEntry(Index1280)
};

/**************************************************************************/
/* The PDO(s) Which could be received                                     */
/**************************************************************************/
/* Computed by strPdoReceive */
#define INDEX_LAST_PDO_RECEIVE  0x140C
#define MAX_COUNT_OF_PDO_RECEIVE 13

#define _CREATE_RXPDO_(RXPDO) \
static  s_pdo_communication_parameter RxPDO ## RXPDO = \
{ 2,      /* Number of entries. Always 2*/\
0x000,  /* Default cobid*/\
0x00    /* Transmission type. See objetdictdef.h*/\
};\
static const subindex Index ## RXPDO[] =\
{\
	{ RO, uint8, sizeof( UNS8 ), (void*)&RxPDO ## RXPDO.count },\
	{ RW, uint32, sizeof( UNS32), (void*)&RxPDO ## RXPDO.cob_id },\
	{ RW, uint8, sizeof( UNS8), (void*)&RxPDO ## RXPDO.type }\
};

// This define the PDO receive entries from index 0x1400 to 0x1402 
_CREATE_RXPDO_(1400)
_CREATE_RXPDO_(1401)
_CREATE_RXPDO_(1402)
_CREATE_RXPDO_(1403)
_CREATE_RXPDO_(1404)
_CREATE_RXPDO_(1405)
_CREATE_RXPDO_(1406)
_CREATE_RXPDO_(1407)
_CREATE_RXPDO_(1408)
_CREATE_RXPDO_(1409)
_CREATE_RXPDO_(140A)
_CREATE_RXPDO_(140B)
_CREATE_RXPDO_(140C)


/* Create the Receive PDO Parameter area. */
__far const indextable   receivePDOParameter[] =
{ 
  DeclareIndexTableEntry(Index1400),
  DeclareIndexTableEntry(Index1401),
  DeclareIndexTableEntry(Index1402),
  DeclareIndexTableEntry(Index1403),
  DeclareIndexTableEntry(Index1404),
  DeclareIndexTableEntry(Index1405),
  DeclareIndexTableEntry(Index1406),
  DeclareIndexTableEntry(Index1407),
  DeclareIndexTableEntry(Index1408),
  DeclareIndexTableEntry(Index1409),
  DeclareIndexTableEntry(Index140A),
  DeclareIndexTableEntry(Index140B),
  DeclareIndexTableEntry(Index140C)
};

/**************************************************************************/
/* The PDO(s) Which could be transmited                                   */
/**************************************************************************/
/* Computed by strPdoTransmit */
#define INDEX_LAST_PDO_TRANSMIT  0x1811
#define MAX_COUNT_OF_PDO_TRANSMIT 18
/** Usually the ID of a transmitting PDO is 0x180 + device_node_id,
*  but the node_id is not known during compilation... so what to do?!
*  the correct values have to be setted up during bootup of the device...
*/
#define _CREATE_TXPDO_(TXPDO) \
static  s_pdo_communication_parameter TxPDO ## TXPDO = \
{ 2,      /* Number of entries. Always 2*/\
0x000,  /* Default cobid*/\
0x00    /* Transmission type. See objetdictdef.h*/\
};\
static const subindex Index ## TXPDO[] =\
{\
	{ RO, uint8, sizeof( UNS8 ), (void*)&TxPDO ## TXPDO.count },\
	{ RW, uint32, sizeof( UNS32), (void*)&TxPDO ## TXPDO.cob_id },\
	{ RW, uint8, sizeof( UNS8), (void*)&TxPDO ## TXPDO.type }\
};

// This define the PDO receive entries from index 0x1800 to 0x1802 
_CREATE_TXPDO_(1800)
_CREATE_TXPDO_(1801)
_CREATE_TXPDO_(1802)
_CREATE_TXPDO_(1803)
_CREATE_TXPDO_(1804)
_CREATE_TXPDO_(1805)
_CREATE_TXPDO_(1806)
_CREATE_TXPDO_(1807)
_CREATE_TXPDO_(1808)
_CREATE_TXPDO_(1809)
_CREATE_TXPDO_(180a)
_CREATE_TXPDO_(180b)
_CREATE_TXPDO_(180c)
_CREATE_TXPDO_(180d)
_CREATE_TXPDO_(180e)
_CREATE_TXPDO_(180f)
_CREATE_TXPDO_(1810)
_CREATE_TXPDO_(1811)
//18

/* Create the Transmit PDO Parameter area. */
__far const indextable   transmitPDOParameter[] =
{ 
  DeclareIndexTableEntry(Index1800),
  DeclareIndexTableEntry(Index1801),
  DeclareIndexTableEntry(Index1802),
  DeclareIndexTableEntry(Index1803),
  DeclareIndexTableEntry(Index1804),
  DeclareIndexTableEntry(Index1805),
  DeclareIndexTableEntry(Index1806),
  DeclareIndexTableEntry(Index1807), 
  DeclareIndexTableEntry(Index1808),
  DeclareIndexTableEntry(Index1809),
  DeclareIndexTableEntry(Index180a),
  DeclareIndexTableEntry(Index180b),
  DeclareIndexTableEntry(Index180c),
  DeclareIndexTableEntry(Index180d),
  DeclareIndexTableEntry(Index180e),
  DeclareIndexTableEntry(Index180f),
  DeclareIndexTableEntry(Index1810),
  DeclareIndexTableEntry(Index1811)
};

/**************************************************************************/
/* PDO Mapping parameters                                                 */
/**************************************************************************/
/* Computed by strPdoParam */

#  define PDO_MAP(index, sub_index, size_variable_in_bits)\
0x ## index ## sub_index ## size_variable_in_bits

/* Beware : 
index                 *must* be writen 4 numbers in hexa
sub_index             *must* be writen 2 numbers in hexa
size_variable_in_UNS8 *must* be writen 2 numbers in hexa
*/
/* Max number of data which can be put in a PDO
   Example, one PDO contains 2 objects, an other contains 5 objects.
   put 
   MAX_COUNT_OF_PDO_MAPPING 5
*/
#define MAX_COUNT_OF_PDO_MAPPING 8

typedef struct td_s_pdo_mapping_parameter  // Index: 0x21
{
/** count of mapping entries
	*/
	UNS8 count;
	/** mapping entries itself.
	*/
	UNS32 object[MAX_COUNT_OF_PDO_MAPPING];
} s_pdo_mapping_parameter;

/**************************************************************************/
/* The mapping area of the PDO received                                   */
/**************************************************************************/
/* Computed by strPdoReceiveMapTop */
/* Note, The index 160x is used to map the PDO 140x. The relation between the two is automatic */
/* Computed by  strCreateRxMap */
#define _CREATE_RXMAP_(RXMAP) \
static  s_pdo_mapping_parameter RxMap ## RXMAP = \
{ 0,\
{\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00)\
 }\
 };\
 const subindex Index ## RXMAP [] =\
{\
  { RW, uint8, sizeof( UNS8 ), (void*)&RxMap ## RXMAP.count },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[0] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[1] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[2] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[3] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[4] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[5] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[6] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&RxMap ## RXMAP.object[7] }\
};
/* Computed by strPdoReceiveMapBot */
#define INDEX_LAST_PDO_MAPPING_RECEIVE  0x160C
_CREATE_RXMAP_(1600)
_CREATE_RXMAP_(1601)
_CREATE_RXMAP_(1602)
_CREATE_RXMAP_(1603)
_CREATE_RXMAP_(1604)
_CREATE_RXMAP_(1605)
_CREATE_RXMAP_(1606)
_CREATE_RXMAP_(1607)
_CREATE_RXMAP_(1608)
_CREATE_RXMAP_(1609)
_CREATE_RXMAP_(160A)
_CREATE_RXMAP_(160B)
_CREATE_RXMAP_(160C)

__far const indextable   RxPDOMappingTable[ ] =
{
  DeclareIndexTableEntry(Index1600),
  DeclareIndexTableEntry(Index1601),
  DeclareIndexTableEntry(Index1602),
  DeclareIndexTableEntry(Index1603),
  DeclareIndexTableEntry(Index1604),
  DeclareIndexTableEntry(Index1605),
  DeclareIndexTableEntry(Index1606),
  DeclareIndexTableEntry(Index1607),
  DeclareIndexTableEntry(Index1608),
  DeclareIndexTableEntry(Index1609),
  DeclareIndexTableEntry(Index160A),
  DeclareIndexTableEntry(Index160B),
  DeclareIndexTableEntry(Index160C)
};

/**************************************************************************/
/* The mapping area of the PDO transmited                                   */
/**************************************************************************/
/* Computed by strPdoTransmitMapTop */
/* Note, The index 18xx is used to map the PDO 1Axxx. The relation between the two is automatic */
/* Computed by  strCreateRxMap */
#define _CREATE_TXMAP_(TXMAP) \
static  s_pdo_mapping_parameter TxMap ## TXMAP = \
{ 0,\
{\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00),\
    PDO_MAP(0000, 00, 00)\
 }\
 };\
 const subindex Index ## TXMAP [] =\
{\
  { RW, uint8, sizeof( UNS8 ), (void*)&TxMap ## TXMAP.count },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[0] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[1] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[2] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[3] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[4] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[5] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[6] },\
  { RW, uint32, sizeof( UNS32 ), (void*)&TxMap ## TXMAP.object[7] }\
};
/* Computed by strPdoTransmitMapBot */
#define INDEX_LAST_PDO_MAPPING_TRANSMIT  0x1a11
_CREATE_TXMAP_(1a00)
_CREATE_TXMAP_(1a01)
_CREATE_TXMAP_(1a02)
_CREATE_TXMAP_(1a03)
_CREATE_TXMAP_(1a04)
_CREATE_TXMAP_(1a05)
_CREATE_TXMAP_(1a06)
_CREATE_TXMAP_(1a07)
_CREATE_TXMAP_(1a08)
_CREATE_TXMAP_(1a09)
_CREATE_TXMAP_(1a0a)
_CREATE_TXMAP_(1a0b)
_CREATE_TXMAP_(1a0c)
_CREATE_TXMAP_(1a0d)
_CREATE_TXMAP_(1a0e)
_CREATE_TXMAP_(1a0f)
_CREATE_TXMAP_(1a10)
_CREATE_TXMAP_(1a11)


__far const indextable   TxPDOMappingTable[ ] =
{
  DeclareIndexTableEntry(Index1a00),
  DeclareIndexTableEntry(Index1a01),
  DeclareIndexTableEntry(Index1a02),
  DeclareIndexTableEntry(Index1a03),
  DeclareIndexTableEntry(Index1a04),
  DeclareIndexTableEntry(Index1a05),
  DeclareIndexTableEntry(Index1a06),
  DeclareIndexTableEntry(Index1a07),
  DeclareIndexTableEntry(Index1a08),
  DeclareIndexTableEntry(Index1a09),
  DeclareIndexTableEntry(Index1a0a),
  DeclareIndexTableEntry(Index1a0b),
  DeclareIndexTableEntry(Index1a0c),
  DeclareIndexTableEntry(Index1a0d),
  DeclareIndexTableEntry(Index1a0e),
  DeclareIndexTableEntry(Index1a0f),
  DeclareIndexTableEntry(Index1a10),
  DeclareIndexTableEntry(Index1a11)
};
//=================================================================================================
//=================================================================================================
//=================================================================================================
// _ача<R Rб  в<_-и   _р_м_--ых б<RкRв
//=================================================================================================
//=================================================================================================
//=================================================================================================
/**************************************************************************/
/* The mapped variables at index 0x2000 - 0x5fff                          */
/**************************************************************************/
//=================================================================================================
// _<_'_ RVV3C
//=================================================================================================
//=================================================================================================
#ifdef PLATA_RVV3C
/********* Index 2000 *********/
	static const UNS8 highestSubIndex_2000 = 11; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },	  //1	
  { RW, uint8, sizeof (UNS8), (void*)&minutes },	  //2
  { RW, uint8, sizeof (UNS8), (void*)&hours },		  //3
  { RW, uint16,sizeof (UNS16),(void*)&day },	      //4
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.Dn},		  //5
  { RW, uint8, sizeof (UNS8), (void*)&Rvv.newDn},     //6
  { RW, uint8, sizeof (UNS8), (void*)&Rvv.nCH},       //7
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.Error},     //8
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.Write},     //9
  { RW, uint8, sizeof (UNS8), (void*)&Rvv.WriteNew},  //10
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.Read}       //11
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Rvv.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};
#endif
//=================================================================================================
//=================================================================================================
// _<_'_ RVV5C
//=================================================================================================
//=================================================================================================
#ifdef PLATA_RVV5C
/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 9; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_2000 },
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.Dn},		  //1
  { RW, uint8, sizeof (UNS8), (void*)&Rvv.newDn},     //2
  { RO, uint16,sizeof (UNS16),(void*)&Rvv.Error},     //3
  { RO, uint16,sizeof (UNS16),(void*)&Rvv.CH_select.word}, //4
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.SelektBl},	  //5
  { RW, uint16,sizeof (UNS16),(void*)&Rvv.NewCH_select.word}, //6
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.SetData},	  //7
  { RO, uint8, sizeof (UNS8), (void*)&Rvv.ReadData},  //8
  { RW, uint8, sizeof (UNS8), (void*)&Rvv.NewSel7}	  //9
  
  
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Rvv.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};
#endif
//=================================================================================================
// _<_'_ KCU1C
//=================================================================================================
//=================================================================================================
#ifdef PLATA_KCU


/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 5; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day },
  { RW, uint8, sizeof (UNS8), (void*)&Kcu.Regim}
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Kcu.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

/********* Index 6000 *********/
#define DIGITAL_INPUT_LAST_TABLE_INDEX 0x6000

static UNS8 highestSubIndex_6000 = 6; // number of subindex - 1
subindex Index6000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6000},
  { RO, uint8, sizeof (UNS8), (void*)&Kcu.CirControl[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Kcu.CirControl[1]},
  { RO, uint8, sizeof (UNS8), (void*)&Kcu.CirControl[2]},
  { RO, uint8, sizeof (UNS8), (void*)&Kcu.RelGroup[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Kcu.RelGroup[1]},
  { RO, uint8, sizeof (UNS8), (void*)&Kcu.RelGroup[2]}
};

__far const indextable digitalInputTable[] = 
{
  DeclareIndexTableEntry(Index6000)
};
#endif
//=================================================================================================
//=================================================================================================
//	DAC-9
//=================================================================================================
//=================================================================================================
#ifdef PLATA_DAC9

/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 10; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8),  (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },//1
  { RW, uint8, sizeof (UNS8), (void*)&minutes },//2
  { RW, uint8, sizeof (UNS8), (void*)&hours },//3
  { RW, uint16,sizeof (UNS16),(void*)&day },//4
  { RW, uint8, sizeof (UNS8), (void*)&Dac9.StRead},//5
  { RW, uint8, sizeof (UNS8), (void*)&Dac9.WriteCoeffFlash},//6
  { RO, uint16, sizeof (UNS16),(void*)&Dac9.SelDAC_CH_cur},//7
  { RW, uint16, sizeof (UNS16),(void*)&Dac9.SelDAC_CH},//8
  { RO, uint16,sizeof (UNS16),(void*)&Dac9.wError},//9
  { RO, uint8,sizeof (UNS8),(void*)&Dac9.Master}//10
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 2; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8)  , (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof(UNS16) , (void*)&Dac9.Info.word},
  { RO, real32,sizeof(REAL32), (void*)&Dac9.Temp}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

/********* Index 6403 *********/
static UNS8 highestSubIndex_6403 = 16; // number of subindex - 1

const subindex Index6403[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6403},
  
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[0]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[1]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[2]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[3]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[4]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[5]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[6]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[7]},
  
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[8]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[9]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[10]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[11]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[12]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[13]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[14]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fADC[15]},
  
};
static UNS8 highestSubIndex_6405 = 16; // number of subindex - 1
const subindex Index6405[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6405},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[0].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[1].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[2].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[3].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[4].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[5].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[6].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[7].ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[8].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[9].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[10].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[11].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[12].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[13].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[14].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[15].ofs},
};
static UNS8 highestSubIndex_6406 = 16; // number of subindex - 1
const subindex Index6406[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6406},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[0].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[1].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[2].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[3].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[4].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[5].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[6].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[7].k},
  
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[8].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[9].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[10].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[11].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[12].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[13].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[14].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[15].k},
};

#define ANALOG_INPUT_LAST_TABLE_INDEX 0x6406
__far const indextable analogInputTable[] = 
{
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6403),
  { NULL, 0 },
  DeclareIndexTableEntry(Index6405),
  DeclareIndexTableEntry(Index6406)
};
/********* Index 6413 *********/
static UNS8 highestSubIndex_6413 = 14; // number of subindex - 1
subindex Index6413[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6413},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[0]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[1]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[2]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[3]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[4]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[5]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[6]},

  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[7]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[8]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[9]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[10]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[11]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[12]},
  { WO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_New[13]}
};
static UNS8 highestSubIndex_6417 = 14; // number of subindex - 1
subindex Index6417[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6417},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[0]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[1]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[2]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[3]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[4]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[5]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[6]},

  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[7]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[8]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[9]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[10]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[11]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[12]},
  { RO, real32, sizeof (REAL32),(void*)&Dac9.fDAC_Cur[13]}
};

static UNS8 highestSubIndex_6418 = 14; // number of subindex - 1
const subindex Index6418[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6418},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[0].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[1].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[2].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[3].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[4].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[5].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[6].ofs},

  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[7].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[8].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[9].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[10].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[11].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[12].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[13].ofs}
};
static UNS8 highestSubIndex_6419 = 14; // number of subindex - 1
const subindex Index6419[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6419},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[0].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[1].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[2].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[3].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[4].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[5].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[6].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[7].k},
  
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[8].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[9].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[10].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[11].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[12].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[13].k}
};

#define ANALOG_OUTPUT_LAST_TABLE_INDEX 0x6419

__far const indextable analogOutputTable[] = 
{
	{ NULL, 0 },//0
	{ NULL, 0 },//1
	{ NULL, 0 },//2
	DeclareIndexTableEntry(Index6413),
	{ NULL, 0 },//4
	{ NULL, 0 },//5
	{ NULL, 0 },//6
	DeclareIndexTableEntry(Index6417),
	DeclareIndexTableEntry(Index6418),
	DeclareIndexTableEntry(Index6419)
};
#endif 
//=================================================================================================
//=================================================================================================
#ifdef PLATA_DAC10

/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 11; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8),  (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },//1
  { RW, uint8, sizeof (UNS8), (void*)&minutes },//2
  { RW, uint8, sizeof (UNS8), (void*)&hours },//3
  { RW, uint16,sizeof (UNS16),(void*)&day },//4
  { RW, uint8, sizeof (UNS8), (void*)&Dac10.WriteCoeffFlash},//5
  { RW, uint16,sizeof (UNS16),(void*)&Dac10.EnOutDac},	//6
  { RO, uint16,sizeof (UNS16),(void*)&Dac10.wError},	//7
  { RO, uint8,sizeof (UNS8),(void*)&Dac10.Master},		//8
  { RO, uint16,sizeof (UNS16),(void*)&Dac10.DiagRele},	//9
  { RO, uint16,sizeof (UNS16),(void*)&Dac10.AddData},	//10
  { RO, uint16,sizeof (UNS16),(void*)&Dac10.TimerMasterError}	//11
  
  
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8)  , (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof(UNS16) , (void*)&Dac10.Info.word},
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

/********* Index 6403 *********/
/*
static UNS8 highestSubIndex_6403 = 12; // number of subindex - 1

const subindex Index6403[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6403},
  
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[0]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[1]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[2]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[3]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[4]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[5]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[6]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[7]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[8]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[9]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[10]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fADC[11]}
};
static UNS8 highestSubIndex_6405 = 12; // number of subindex - 1
const subindex Index6405[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6405},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[0].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[1].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[2].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[3].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[4].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[5].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[6].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[7].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[8].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[9].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[10].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[11].ofs}
};
static UNS8 highestSubIndex_6406 = 12; // number of subindex - 1
const subindex Index6406[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6406},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[0].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[1].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[2].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[3].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[4].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[5].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[6].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[7].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[8].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[9].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[10].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_ADC[11].k}
};

#define ANALOG_INPUT_LAST_TABLE_INDEX 0x6406
__far const indextable analogInputTable[] = 
{
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6403),
  { NULL, 0 },
  DeclareIndexTableEntry(Index6405),
  DeclareIndexTableEntry(Index6406)
};*/
/********* Index 6413 *********/
static UNS8 highestSubIndex_6413 = 12; // number of subindex - 1
subindex Index6413[] = 
{
	{ RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6413},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[0]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[1]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[2]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[3]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[4]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[5]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[6]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[7]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[8]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[9]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[10]},
	{ WO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_New[11]}
};
static UNS8 highestSubIndex_6417 = 12; // number of subindex - 1
subindex Index6417[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6417},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[0]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[1]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[2]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[3]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[4]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[5]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[6]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[7]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[8]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[9]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[10]},
  { RO, real32, sizeof (REAL32),(void*)&Dac10.fDAC_Set[11]}
};

static UNS8 highestSubIndex_6418 = 12; // number of subindex - 1
const subindex Index6418[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6418},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[0].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[1].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[2].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[3].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[4].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[5].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[6].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[7].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[8].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[9].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[10].ofs},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[11].ofs}
};
static UNS8 highestSubIndex_6419 = 12; // number of subindex - 1
const subindex Index6419[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6419},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[0].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[1].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[2].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[3].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[4].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[5].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[6].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[7].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[8].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[9].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[10].k},
  { RW, real32, sizeof (REAL32),(void*)&TarrRAM_DAC[11].k}
};

#define ANALOG_OUTPUT_LAST_TABLE_INDEX 0x6419

__far const indextable analogOutputTable[] = 
{
	{ NULL, 0 },//0
	{ NULL, 0 },//1
	{ NULL, 0 },//2
	DeclareIndexTableEntry(Index6413),
	{ NULL, 0 },//4
	{ NULL, 0 },//5
	{ NULL, 0 },//6
	DeclareIndexTableEntry(Index6417),
	DeclareIndexTableEntry(Index6418),
	DeclareIndexTableEntry(Index6419)
};
static UNS8 highestSubIndex_6000 = 12; // number of subindex - 1
subindex Index6000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6000},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[1]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[2]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[3]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[4]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[5]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[6]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[7]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[8]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[9]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[10]},
  { RO, uint8, sizeof (UNS8), (void*)&Dac10.DIN[11]}
};

#define DIGITAL_INPUT_LAST_TABLE_INDEX 0x6000
__far const indextable digitalInputTable[] = 
{
  DeclareIndexTableEntry(Index6000)
};


#endif 
//=================================================================================================
//=================================================================================================
// ADC5(6)C
//=================================================================================================
//=================================================================================================

#ifdef PLATA_ADC


/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 7; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },//1
  { RW, uint8, sizeof (UNS8), (void*)&minutes },//2
  { RW, uint8, sizeof (UNS8), (void*)&hours },//3
  { RW, uint16,sizeof (UNS16), (void*)&day },//4
  { RW, uint8, sizeof (UNS8), (void*)&Adc.StRead},//5
  { RW, uint8, sizeof (UNS8), (void*)&Adc.WriteCoeffFlash},//6
  { RO, uint8, sizeof (UNS8), (void*)&Adc.ErrADC}//7
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Adc.Info.word}
};

/********* Index 2002 *********/
static UNS8 highestSubIndex_2002 = 1; // number of subindex - 1

subindex Index2002[] =
{
	{ RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2002},
    { RO, uint16,sizeof(UNS16), (void*)&Adc.Temp }
}; 

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2002
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001),
  DeclareIndexTableEntry(Index2002)
};

/********* Index 6403 *********/
static UNS8 highestSubIndex_6403 = 32; // number of subindex - 1

const subindex Index6403[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6403},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[0]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[1]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[2]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[3]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[4]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[5]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[6]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[7]},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[8]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[9]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[10]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[11]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[12]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[13]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[14]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[15]},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[16]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[17]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[18]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[19]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[20]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[21]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[22]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[23]},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[24]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[25]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[26]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[27]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[28]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[29]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[30]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[31]}

};
static UNS8 highestSubIndex_6405 = 35; // number of subindex - 1
const subindex Index6405[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6405},
  { RW, real32, 0,NULL},
  { RW, real32, 0,NULL},
  //============================================
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[0].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[1].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[2].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[3].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[4].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[5].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[6].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[7].Ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[8].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[9].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[10].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[11].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[12].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[13].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[14].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[15].Ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[16].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[17].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[18].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[19].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[20].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[21].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[22].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[23].Ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[24].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[25].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[26].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[27].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[28].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[29].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[30].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[31].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[32].Ofs},
  //------
};
static UNS8 highestSubIndex_6406 = 33; // number of subindex - 1
const subindex Index6406[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6406},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[0].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[1].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[2].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[3].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[4].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[5].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[6].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[7].K},
  
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[8].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[9].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[10].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[11].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[12].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[13].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[14].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[15].K},
  
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[16].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[17].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[18].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[19].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[20].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[21].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[22].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[23].K},
  
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[24].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[25].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[26].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[27].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[28].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[29].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[30].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[31].K},
  { RW, real32, sizeof (REAL32),(void*)&k_33_new[32].K}
};

#define ANALOG_INPUT_LAST_TABLE_INDEX 0x6406
__far const indextable analogInputTable[] = 
{
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6403),
  { NULL, 0 },
  DeclareIndexTableEntry(Index6405),
  DeclareIndexTableEntry(Index6406)
};
/********* Index 6413 *********/
static UNS8 highestSubIndex_6413 = 1; // number of subindex - 1
subindex Index6413[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6413},
  { RW, real32, sizeof (REAL32),(void*)&Adc.newDAC}
};

#define ANALOG_OUTPUT_LAST_TABLE_INDEX 0x6413
__far const indextable analogOutputTable[] = 
{
  { NULL, 0 },//0
  { NULL, 0 },//1
  { NULL, 0 },//2
  DeclareIndexTableEntry(Index6413)
};

#endif
//=================================================================================================
//=================================================================================================
// ADC8C
//=================================================================================================
//=================================================================================================

#ifdef PLATA_ADC8


/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 5; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },//1
  { RW, uint8, sizeof (UNS8), (void*)&minutes },//2
  { RW, uint8, sizeof (UNS8), (void*)&hours },//3
  { RW, uint16,sizeof (UNS16), (void*)&day },//4
  { RW, uint8, sizeof (UNS8), (void*)&Adc.WriteCoeffFlash}//5
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Adc.Info.word}
};

/********* Index 2002 *********/

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

/********* Index 6403 *********/
static UNS8 highestSubIndex_6403 = 24; // number of subindex - 1

const subindex Index6403[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6403},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[0]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[1]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[2]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[3]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[4]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[5]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[6]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[7]},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[8]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[9]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[10]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[11]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[12]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[13]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[14]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[15]},
  
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[16]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[17]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[18]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[19]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[20]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[21]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[22]},
  { RO, real32, sizeof (REAL32),(void*)&Adc.fADC[23]}
};
static UNS8 highestSubIndex_6405 = 24; // number of subindex - 1
const subindex Index6405[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6405},
  //============================================
  { RW, real32, sizeof (REAL32),(void*)&k_new[0].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[1].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[2].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[3].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[4].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[5].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[6].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[7].Ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&k_new[8].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[9].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[10].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[11].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[12].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[13].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[14].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[15].Ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&k_new[16].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[17].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[18].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[19].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[20].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[21].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[22].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&k_new[23].Ofs},
  //------
};
static UNS8 highestSubIndex_6406 = 24; // number of subindex - 1
const subindex Index6406[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6406},
  { RW, real32, sizeof (REAL32),(void*)&k_new[0].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[1].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[2].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[3].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[4].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[5].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[6].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[7].K},
  
  { RW, real32, sizeof (REAL32),(void*)&k_new[8].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[9].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[10].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[11].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[12].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[13].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[14].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[15].K},
  
  { RW, real32, sizeof (REAL32),(void*)&k_new[16].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[17].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[18].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[19].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[20].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[21].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[22].K},
  { RW, real32, sizeof (REAL32),(void*)&k_new[23].K},
};

#define ANALOG_INPUT_LAST_TABLE_INDEX 0x6406
__far const indextable analogInputTable[] = 
{
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6403),
  { NULL, 0 },
  DeclareIndexTableEntry(Index6405),
  DeclareIndexTableEntry(Index6406)
};
#endif
//=================================================================================================
//=================================================================================================
// AVV2C
//=================================================================================================
//=================================================================================================
#ifdef PLATA_AVV2C

static UNS8 highestSubIndex_2000 = 9; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof(UNS8), (void*)&seconds },				//1
  { RW, uint8, sizeof(UNS8), (void*)&minutes },				//2
  { RW, uint8, sizeof(UNS8), (void*)&hours },  				//3
  { RW, uint16,sizeof(UNS16),(void*)&day },    				//4
  { RW, uint8, sizeof(UNS8), (void*)&Avv.newRegim_AVV},		//5
  { RO, uint8, sizeof(UNS8), (void*)&day}, 					//6
  { RO, uint8, sizeof(UNS8), (void*)&Avv.Status}, 			//7
  { RW, uint8,sizeof(UNS8),   (void*)&Avv.WriteCoeffFlash},	//8
  { RW, uint8,sizeof(UNS8),   (void*)&Avv.RegimWork}		//9
  
};

static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Avv.Info.word}
};
/*
static UNS8 highestSubIndex_2002 = 10; // number of subindex - 1
subindex Index2002[] =
{
	{ RO, uint8, sizeof(UNS8) , (void*)&highestSubIndex_2002},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[0]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[0]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[2]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[4]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[6]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[8]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[10]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[12]},
	{ RO, uint16,sizeof(UNS16), (void*)&Avv.RegRead[14]}//,
//	{ RW, uint16,sizeof(UNS16), (void*)&Avv.ConfigADC}
}; */

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)/*,
  DeclareIndexTableEntry(Index2002)*/
};

/*static UNS8 highestSubIndex_6402 = 5; // number of subindex - 1
subindex Index6402[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6402},
  { RW, uint32, sizeof (UNS32), (void*)&Avv.rADC[0]},
  { RW, uint32, sizeof (UNS32), (void*)&Avv.rADC[1]},
  { RW, uint32, sizeof (UNS32), (void*)&Avv.rADC[2]},
  { RW, uint32, sizeof (UNS32), (void*)&Avv.rADC[3]},	
  { RW, uint32, sizeof (UNS32), (void*)&Avv.rADC[4]},	
  { RW, uint32, sizeof (UNS32), (void*)&Avv.rADC[5]}
};*/
static UNS8 highestSubIndex_6403 = 6; // number of subindex - 1
subindex Index6403[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_6403},
  { RO, real32, sizeof (REAL32),(void*)&Avv.fADC[0]},
  { RO, real32, sizeof (REAL32),(void*)&Avv.fADC[1]},
  { RO, real32, sizeof (REAL32),(void*)&Avv.fADC[2]},
  { RO, real32, sizeof (REAL32),(void*)&Avv.fADC[3]},
  { RO, real32, sizeof (REAL32),(void*)&Avv.fADC[4]},
  { RO, real32, sizeof (REAL32),(void*)&Avv.fADC[5]},
};


#define ANALOG_INPUT_LAST_TABLE_INDEX  0x6403
__far const indextable analogInputTable[] = 
{
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  //DeclareIndexTableEntry(Index6402),
  DeclareIndexTableEntry(Index6403)
};

#define ANALOG_INPUT_SET_LAST_TABLE_INDEX 0x642F
static UNS8 highestSubIndex_642E = 12; // number of subindex - 1
const subindex Index642E[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_642E},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][0].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][1].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][2].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][3].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][4].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][5].Ofs},
  
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][0].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][1].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][2].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][3].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][4].Ofs},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][5].Ofs}
};
static UNS8 highestSubIndex_642F = 12; // number of subindex - 1
const subindex Index642F[] = 
{
  { RO, uint8, 	sizeof (UNS8), 	(void*)&highestSubIndex_642F},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][0].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][1].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][2].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][3].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][4].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[0][5].K},
  
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][0].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][1].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][2].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][3].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][4].K},
  { RW, real32, sizeof (REAL32),(void*)&Tarir_new.ADC_New[1][5].K}
};

__far const indextable analogInputSetTable[] = 
{
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	DeclareIndexTableEntry(Index642E),
	DeclareIndexTableEntry(Index642F)
};


static UNS8 highestSubIndex_6413 = 1; // number of subindex - 1
subindex Index6413[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6413},
  { RW, uint16, sizeof (REAL32), (void*)&Avv.fNewDAC},
};
static UNS8 highestSubIndex_6417 = 1; // number of subindex - 1
subindex Index6417[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6417},
  { RO, uint16, sizeof (REAL32), (void*)&Avv.fDAC},
};
#define ANALOG_OUTPUT_LAST_TABLE_INDEX 0x6417
__far const indextable analogOutputTable[] = 
{
  { NULL, 0 },//0
  { NULL, 0 },//1
  { NULL, 0 },//2
  DeclareIndexTableEntry(Index6413),
  { NULL, 0 },//4
  { NULL, 0 },//5
  { NULL, 0 },//6
  DeclareIndexTableEntry(Index6417)//17
};

#define ANALOG_OUTPUT_SET_LAST_TABLE_INDEX 0x6442

static UNS8 highestSubIndex_6441 = 1; // number of subindex - 1
subindex Index6441[] = 
{
	{ RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6441},
  	{ RW, real32, sizeof (REAL32),(void*)&Tarir_new.DAC_New.Ofs}
};
static UNS8 highestSubIndex_6442 = 1; // number of subindex - 1
subindex Index6442[] = 
{
	{ RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6442},
  	{ RW, real32, sizeof (REAL32),(void*)&Tarir_new.DAC_New.K}
};

__far const indextable analogOutputSetTable[] = 
{
	{ NULL, 0 },
	DeclareIndexTableEntry(Index6441),
	DeclareIndexTableEntry(Index6442)
};

#endif
//=================================================================================================
//=================================================================================================
// FSU14C - FSU16-K
//=================================================================================================
//=================================================================================================
#ifdef PLATA_FSU

static const UNS8 highestSubIndex_2000 = 2; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.St },
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Timer }
};
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Fsu.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

/********* Index 6200 *********/
static UNS8 highestSubIndex_6200 = 3; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Prin},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Prin)+1)},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Prin)+2)},
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 3; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.State},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.State)+1)},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.State)+2)},
};
/********* Index 6209 *********/
static UNS8 highestSubIndex_6209 = 3; // number of subindex - 1
subindex Index6209[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6209},
  { RO, uint8, sizeof (UNS8), (void*)(&Fsu.Test)},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Test)+1)},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Test)+2)},
};
#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6209
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6209)
};
#endif
//=================================================================================================
//=================================================================================================
// FSU28
//=================================================================================================
//=================================================================================================
#ifdef PLATA_FSU28

static const UNS8 highestSubIndex_2000 = 4; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day }
};

static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Fsu.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

/********* Index 6200 *********/
static UNS8 highestSubIndex_6200 = 3; // number of subindex - 1
subindex Index6200[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Prin},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Prin)+1)},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Prin)+2)},
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 3; // number of subindex - 1
subindex Index6201[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RO, uint8, sizeof (UNS8), (void*)&Fsu.State},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.State)+1)},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.State)+2)},
};
/********* Index 6209 *********/
static UNS8 highestSubIndex_6209 = 3; // number of subindex - 1
subindex Index6209[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6209},
  { RO, uint8, sizeof (UNS8), (void*)(&Fsu.Test)},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Test)+1)},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu.Test)+2)},
};
#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6209
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6209)
};
#endif
//=================================================================================================

//=================================================================================================
//=================================================================================================
// FSU15_C
//=================================================================================================
//=================================================================================================
#ifdef PLATA_FSU15_C

static const UNS8 highestSubIndex_2000 = 4; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day }
};

static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Fsu15.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6200 = 2; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu15.Prin},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu15.Prin)+1)}
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 2; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu15.State},
  { RW, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu15.State)+1)}
 };
/********* Index 6209 *********/
static UNS8 highestSubIndex_6209 = 2; // number of subindex - 1
subindex Index6209[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6209},
  { RO, uint8, sizeof (UNS8), (void*)(&Fsu15.Test)},
  { RO, uint8, sizeof (UNS8), (void*)((UNS8 *)(&Fsu15.Test)+1)}
};

#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6209
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6209)
};
#endif
//=================================================================================================
//=================================================================================================
// _<_'_ FSU19
//=================================================================================================
//=================================================================================================
#ifdef PLATA_FSU19

static const UNS8 highestSubIndex_2000 = 4; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day }
};

static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Fsu.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6200 = 4; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Prin[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Prin[1]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Prin[2]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.Prin[3]}
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 4; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.State[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.State[1]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.State[2]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu.State[3]}
};
#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6209
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201)
};
#endif
//=================================================================================================
//=================================================================================================
// _<_'_ FSU22
//=================================================================================================
//=================================================================================================
#ifdef PLATA_FSU22

static const UNS8 highestSubIndex_2000 = 4; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day }
};

static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Fsu22.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6200 = 2; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22.Prin.byte[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22.Prin.byte[1]}
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 2; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22.State.byte[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22.State.byte[1]}
 };
/********* Index 6209 *********/
static UNS8 highestSubIndex_6209 = 2; // number of subindex - 1
subindex Index6209[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6209},
  { RO, uint8, sizeof (UNS8), (void*)&Fsu22.Test.byte[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Fsu22.Test.byte[1]}
};

#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6209
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6209)
};
#endif
//=================================================================================================
//=================================================================================================
// _<_'_ FSU22-C
//=================================================================================================
//=================================================================================================
#ifdef PLATA_FSU22C

static const UNS8 highestSubIndex_2000 = 4; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day }
};

static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Fsu22C.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6200 = 2; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22C.Prin[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22C.Prin[1]}
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 2; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22C.State[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Fsu22C.State[1]}
 };
/********* Index 6209 *********/
static UNS8 highestSubIndex_6209 = 2; // number of subindex - 1
subindex Index6209[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6209},
  { RO, uint8, sizeof (UNS8), (void*)&Fsu22C.Test[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Fsu22C.Test[1]}
};

#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6209
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6209)
};
#endif
//=================================================================================================
//=================================================================================================
// _<_'_ NDD16_C - NDD18-CV - NDD17-K
//=================================================================================================
//=================================================================================================
#ifdef PLATA_NDD

static const UNS8 highestSubIndex_2000 = 4; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint8, sizeof (UNS8), (void*)&seconds },
  { RW, uint8, sizeof (UNS8), (void*)&minutes },
  { RW, uint8, sizeof (UNS8), (void*)&hours },
  { RW, uint16, sizeof (UNS16), (void*)&day }
};
//================2001=========================================
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
#ifdef PLATA_NDD
  { RO, uint16,sizeof (UNS16), (void*)&Ndd.Info.word},
#endif
};
#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6000 = 4; // number of subindex - 1
subindex Index6000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6000},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[1]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[2]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[3]}
};
/********* Index 6009 *********/
static UNS8 highestSubIndex_6009 = 4; // number of subindex - 1
subindex Index6009[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6009},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[1]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[2]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[3]}
};

#define DIGITAL_INPUT_LAST_TABLE_INDEX 0x6009
__far const indextable digitalInputTable[] = 
{
  DeclareIndexTableEntry(Index6000),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6009)
};

#endif
//=================================================================================================
// _<_'_ NDD21
//=================================================================================================
//=================================================================================================
#ifdef PLATA_NDD21

static const UNS8 highestSubIndex_2000 = 5; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8,	sizeof(UNS8),	(void*)&highestSubIndex_2000 },
  { RW, uint8,	sizeof (UNS8),	(void*)&seconds },
  { RW, uint8,	sizeof (UNS8),	(void*)&minutes },
  { RW, uint8,	sizeof (UNS8),	(void*)&hours },
  { RW, uint16,	sizeof (UNS16),	(void*)&day },
  { RW, uint8,	sizeof (UNS8),	(void*)&Ndd.stOff }
};
//================2001=========================================
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Ndd.Info.word}
};
#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6000 = 2; // number of subindex - 1
subindex Index6000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6000},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[1]}
};
/********* Index 6009 *********/
static UNS8 highestSubIndex_6009 = 2; // number of subindex - 1
subindex Index6009[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6009},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[1]}
};

#define DIGITAL_INPUT_LAST_TABLE_INDEX 0x6009
__far const indextable digitalInputTable[] = 
{
  DeclareIndexTableEntry(Index6000),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6009)
};

#endif
//=================================================================================================
// _<_'_ NDD20
//=================================================================================================
//=================================================================================================
#ifdef PLATA_NDD20

//================2001=========================================
static UNS8 highestSubIndex_2001 = 11; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Ndd.Info.word},
  { RO, uint8,sizeof (UNS8), (void*)&Ndd.valid[0]},
  { RO, uint8,sizeof (UNS8), (void*)&Ndd.valid[1]},
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.T_1},		//4
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.T_2},		//5
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.T_3},		//6
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.T_4},
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.IN_1},
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.IN_2},
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.IN_3},
  { RW, uint8,sizeof (UNS8), (void*)&Ndd.IN_4}
  
};
#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  {NULL,0},
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6000 = 2; // number of subindex - 1
subindex Index6000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6000},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[1]}
};
/********* Index 6009 *********/
static UNS8 highestSubIndex_6009 = 2; // number of subindex - 1
subindex Index6009[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6009},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[1]}
};

#define DIGITAL_INPUT_LAST_TABLE_INDEX 0x6009
__far const indextable digitalInputTable[] = 
{
  DeclareIndexTableEntry(Index6000),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6009)
};

static UNS8 highestSubIndex_6200 = 1; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Ndd.PowerNew}
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 1; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.PowerOld}
};

#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6201
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201)
};

#endif

//=================================================================================================
#ifdef PLATA_NDD20P1

//================2001=========================================
static UNS8 highestSubIndex_2001 = 1; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Ndd.Info.word},
};
#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  {NULL,0},
  DeclareIndexTableEntry(Index2001)
};

static UNS8 highestSubIndex_6000 = 2; // number of subindex - 1
subindex Index6000[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6000},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.state[1]}
};
/********* Index 6009 *********/
static UNS8 highestSubIndex_6009 = 2; // number of subindex - 1
subindex Index6009[] = 
{
  { RO, uint8, sizeof (UNS8), (void*)&highestSubIndex_6009},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[0]},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.test[1]}
};

#define DIGITAL_INPUT_LAST_TABLE_INDEX 0x6009
__far const indextable digitalInputTable[] = 
{
  DeclareIndexTableEntry(Index6000),
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  { NULL, 0 },
  DeclareIndexTableEntry(Index6009)
};

static UNS8 highestSubIndex_6200 = 1; // number of subindex - 1
subindex Index6200[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6200},
  { RW, uint8, sizeof (UNS8), (void*)&Ndd.PowerNew}
};
/*-----------------------------------------------------------*/
static UNS8 highestSubIndex_6201 = 1; // number of subindex - 1
subindex Index6201[] = 
{
  { RW, uint8, sizeof (UNS8), (void*)&highestSubIndex_6201},
  { RO, uint8, sizeof (UNS8), (void*)&Ndd.PowerOld}
};

#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0x6201
__far const indextable digitalOutputTable[] = 
{
  DeclareIndexTableEntry(Index6200),
  DeclareIndexTableEntry(Index6201)
};

#endif
//=================================================================================================
#ifdef PLATA_TEST

static const UNS8 highestSubIndex_2000 = 30; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2000 },
  { RW, uint16, sizeof (UNS16), (void*)&Test.w_data[0]},
  { RW, uint16, sizeof (UNS16), (void*)&Test.w_data[1]},
  { RW, uint16, sizeof (UNS16), (void*)&Test.w_data[2]},
  { RW, uint16, sizeof (UNS16), (void*)&Test.w_data[3]},
  { RW, uint16, sizeof (UNS16), (void*)&Test.w_data[4]},
  
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[0]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[1]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[2]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[3]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[4]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[5]},

  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[6]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[7]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[8]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[9]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[10]},
  
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[11]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[12]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[13]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[14]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[15]},

  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[16]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[17]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[18]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[19]},
  { RW, real32, sizeof (REAL32), (void*)&Test.f_data[20]},
  
  { RW, uint8, sizeof (UNS8), (void*)&Test.b_data[0]},
  { RW, uint8, sizeof (UNS8), (void*)&Test.b_data[1]},
  { RW, uint8, sizeof (UNS8), (void*)&Test.b_data[2]},
  { RW, uint8, sizeof (UNS8), (void*)&Test.b_data[3]},
  { RW, uint8, sizeof (UNS8), (void*)&Test.b_data[4]}
  
};
//================2001=========================================
#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2000
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000)
};


#endif
//=================================================================================================
//=================================================================================================
//=================================================================================================
// RVV6
//=================================================================================================
//=================================================================================================
#ifdef PLATA_RVV6
/********* Index 2000 *********/
static const UNS8 highestSubIndex_2000 = 50; // number of subindex - 1
subindex Index2000[] = 
{
  { RO, uint8,	sizeof (UNS8), (void*)&highestSubIndex_2000 },
  { RO, uint16,	sizeof (UNS16), (void*)&Rvv.Error},					//	1
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.EnableChange},			//	2
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.NewEnableChange},		//	3
  { RO, uint32,	sizeof (UNS32), (void*)&Rvv.SelectBlockOld},		//	4
  { RW, uint32,	sizeof (UNS32), (void*)&Rvv.SelectBlockNew},		//	5
  //=====================================================================
  // 1 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[0].Old[0]},		//	6
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[0].Old[1]},		//	7
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[0].New[0]},		//	8
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[0].New[1]},		//	9
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[0].Error},			//	10
  //=====================================================================
  // 2 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[1].Old[0]},		//	11
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[1].Old[1]},		//	12 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[1].New[0]},		//	13
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[1].New[1]},		//	14
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[1].Error},			//	15
  //=====================================================================
  // 3 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[2].Old[0]},		//	16
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[2].Old[1]},		//	17 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[2].New[0]},		//	18
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[2].New[1]},		//	19
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[2].Error},			//	20
  //=====================================================================
  // 4 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[3].Old[0]},		//	21
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[3].Old[1]},		//	22 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[3].New[0]},		//	23
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[3].New[1]},		//	24
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[3].Error},			//	25
  //=====================================================================
  // 5 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[4].Old[0]},		//	26
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[4].Old[1]},		//	27 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[4].New[0]},		//	28
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[4].New[1]},		//	29
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[4].Error},			//	30
  //=====================================================================
  // 6 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[5].Old[0]},		//	31
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[5].Old[1]},		//	32 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[5].New[0]},		//	33
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[5].New[1]},		//	34
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[5].Error},			//	35
  //====================================================================
  // 7 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[6].Old[0]},		//	36
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[6].Old[1]},		//	37 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[6].New[0]},		//	38
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[6].New[1]},		//	39
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[6].Error},			//	40
  //=====================================================================
  // 8 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[7].Old[0]},		//	41
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[7].Old[1]},		//	42 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[7].New[0]},		//	43
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[7].New[1]},		//	44
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[7].Error},			//	45
  //=====================================================================
  // 9 блок
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[8].Old[0]},		//	46
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[8].Old[1]},		//	47 
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[8].New[0]},		//	48
  { RW, uint8,	sizeof (UNS8), (void*)&Rvv.Block[8].New[1]},		//	49
  { RO, uint8,	sizeof (UNS8), (void*)&Rvv.Block[8].Error}			//	50
};
/********* Index 2001 *********/
static UNS8 highestSubIndex_2001 = 2; // number of subindex - 1
subindex Index2001[] = 
{
  { RO, uint8, sizeof(UNS8), (void*)&highestSubIndex_2001 },
  { RO, uint16,sizeof (UNS16), (void*)&Rvv.Info.word}
};

#define MANUFACTURER_SPECIFIC_LAST_INDEX 0x2001
__far const indextable manufacturerProfileTable[] = 
{
  DeclareIndexTableEntry(Index2000),
  DeclareIndexTableEntry(Index2001)
};
#endif
//=================================================================================================
#ifndef MANUFACTURER_SPECIFIC_LAST_INDEX
	#define MANUFACTURER_SPECIFIC_LAST_INDEX 0
	__far const indextable manufacturerProfileTable[] = {{ NULL, 0 }};
#endif

#ifndef DIGITAL_INPUT_LAST_TABLE_INDEX
	#define DIGITAL_INPUT_LAST_TABLE_INDEX 0
	__far const indextable digitalInputTable[] = {{ NULL, 0 }};
#endif

#ifndef DIGITAL_OUTPUT_LAST_TABLE_INDEX
	#define DIGITAL_OUTPUT_LAST_TABLE_INDEX 0
	__far const indextable digitalOutputTable[]= {{ NULL, 0 }};
#endif

#ifndef ANALOG_OUTPUT_LAST_TABLE_INDEX
	#define ANALOG_OUTPUT_LAST_TABLE_INDEX 0
	__far const indextable analogOutputTable[] = {{ NULL, 0 }};
#endif

#ifndef	ANALOG_OUTPUT_SET_LAST_TABLE_INDEX
	#define ANALOG_OUTPUT_SET_LAST_TABLE_INDEX 0
	__far const indextable analogOutputSetTable[] = {{ NULL, 0 }};
#endif 

#ifndef ANALOG_INPUT_LAST_TABLE_INDEX
	#define ANALOG_INPUT_LAST_TABLE_INDEX 0
	__far const indextable analogInputTable[]= {{ NULL, 0 }};
#endif

#ifndef	ANALOG_INPUT_SET_LAST_TABLE_INDEX
	#define ANALOG_INPUT_SET_LAST_TABLE_INDEX 0
	__far const indextable analogInputSetTable[] = {{ NULL, 0 }};
#endif 

//=================================================================================================
//=================================================================================================


UNS8 count_sync[2][MAX_COUNT_OF_PDO_TRANSMIT];

#define COMM_PROFILE_LAST 0x1018

/* Should not be modified */
__far const dict_cste dict_cstes = {
COMM_PROFILE_LAST,
INDEX_LAST_SDO_SERVER,            
DEF_MAX_COUNT_OF_SDO_SERVER,	    
INDEX_LAST_SDO_CLIENT,	          
DEF_MAX_COUNT_OF_SDO_CLIENT,	    
INDEX_LAST_PDO_RECEIVE,	          
MAX_COUNT_OF_PDO_RECEIVE,	        
INDEX_LAST_PDO_TRANSMIT,	        
MAX_COUNT_OF_PDO_TRANSMIT,	      
INDEX_LAST_PDO_MAPPING_RECEIVE,	  
INDEX_LAST_PDO_MAPPING_TRANSMIT,

MANUFACTURER_SPECIFIC_LAST_INDEX,

DIGITAL_INPUT_LAST_TABLE_INDEX,
DIGITAL_OUTPUT_LAST_TABLE_INDEX,

ANALOG_OUTPUT_LAST_TABLE_INDEX,
ANALOG_OUTPUT_SET_LAST_TABLE_INDEX,

ANALOG_INPUT_LAST_TABLE_INDEX,
ANALOG_INPUT_SET_LAST_TABLE_INDEX,

NB_OF_HEARTBEAT_PRODUCERS	  
};  
