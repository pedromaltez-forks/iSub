//
//  iSubAppDelegate.h
//  iSub
//
//  Created by Ben Baron on 2/27/10.
//  Copyright Ben Baron 2010. All rights reserved.
//

#ifndef iSub_iSubAppDelegate_h
#define iSub_iSubAppDelegate_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class BBSplitViewController, iPadRootViewController, InitialDetailViewController, LoadingScreen, FMDatabase, iPhoneStreamingPlayerViewController, SettingsViewController, FoldersViewController, AudioStreamer, IntroViewController, ISMSStatusLoader, MPMoviePlayerController, HTTPServer, ServerListViewController, EX2Reachability, ItemViewController, ItemViewController, SidePanelController, Server, NetworkStatus;

@interface iSubAppDelegate : NSObject <UIApplicationDelegate>

@property (strong) iPadRootViewController *ipadRootViewController;

@property (strong) HTTPServer *hlsProxyServer;

@property (strong) ISMSStatusLoader *statusLoader;

// New UI
@property (nonatomic, strong) UIWindow *window;
@property (strong) SidePanelController *sidePanelController;

// Network connectivity objects and variables
//
@property (strong) NetworkStatus *networkStatus;
@property (readonly) BOOL isWifi;

// Multitasking stuff
@property UIBackgroundTaskIdentifier backgroundTask;
@property BOOL isInBackground;

@property (strong) NSURL *referringAppUrl;

@property (strong) MPMoviePlayerController *moviePlayer;

- (void)backToReferringApp;

+ (iSubAppDelegate *)si;

- (void)enterOnlineModeForce;
- (void)enterOfflineModeForce;

//- (void)loadFlurryAnalytics;
- (void)loadHockeyApp;

- (void)reachabilityChanged;

- (void)showSettings;

- (void)batteryStateChanged:(NSNotification *)notification;

- (void)checkServer;

- (NSString *)zipAllLogFiles;

- (void)checkWaveBoxRelease;

- (void)switchServerTo:(Server *)server redirectUrl:(NSString *)redirectionUrl;


@end

#endif

