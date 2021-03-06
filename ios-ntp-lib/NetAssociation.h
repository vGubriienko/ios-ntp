/*╔══════════════════════════════════════════════════════════════════════════════════════════════════╗
  ║ NetAssociation.h                                                                                 ║
  ║                                                                                                  ║
  ║ Created by Gavin Eadie on Nov03/10 ... Copyright 2010-14 Ramsay Consulting. All rights reserved. ║
  ║──────────────────────────────────────────────────────────────────────────────────────────────────║
  ║ This NetAssociation manages the communication and time calculations for one server.              ║
  ║                                                                                                  ║
  ║ Multiple servers are used in a process in which each client/server pair (association) works to   ║
  ║ obtain its own best version of the time.  The client sends small UDP packets to the server and   ║
  ║ the server overwrites certain fields in the packet and returns it immediately.  As each packet   ║
  ║ is received, the offset between the client's network time and the system clock is derived with   ║
  ║ associated statistics.                                                                           ║
  ║                                                                                                  ║
  ║ Each association makes a best effort at obtaining an accurate time and makes it available as a   ║
  ║ property.  Another process may use this to select, cluster, and combine the various servers'     ║
  ║ data to determine the most accurate and reliable candidates to provide an overall best time.     ║
  ╚══════════════════════════════════════════════════════════════════════════════════════════════════╝*/

#import <UIKit/UIKit.h>
#import <CocoaAsyncSocket/GCDAsyncUdpSocket.h>

@class NetAssociation;
@protocol NetAssociationDelegate <NSObject>

- (void) netAssociationDidUpdateState:(NetAssociation *)sender;

@end


@interface NetAssociation : NSObject

@property (nonatomic, readonly) double    dispersion;         // milliSeconds
@property (nonatomic, readonly) NSString *pool;               // ntp pool "0.pool.ntp.org"
@property (nonatomic, readonly) NSString *serverIPAddress;    // server address "123.45.67.89"
@property (nonatomic, readonly) BOOL      active;             // is this clock running yet?
@property (nonatomic, readonly) BOOL      trusty;             // is this clock trustworthy
@property (nonatomic, readonly) double    offset;             // offset from device time (secs)

/**
 Used to trysty/unstrusty NTP server, typical values (0.001..-0.1) in S.
 Default value is 0.025 S
 */
@property (nonatomic) double timeDeviationDrift;
@property (nonatomic, weak) id<NetAssociationDelegate> delegate;

- (instancetype) init NS_UNAVAILABLE;
/*┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
  ┃ create a NetAssociation with the provided server name ..                                         ┃
  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛*/

- (instancetype) initWithServerPool:(NSString *)pool IPAddress:(NSString *) serverIPAddress NS_DESIGNATED_INITIALIZER;

- (void) enable;
- (void) finish;

@end

