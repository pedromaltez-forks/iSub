//
//  SUSServerPlaylistDAO.m
//  iSub
//
//  Created by Benjamin Baron on 11/1/11.
//  Copyright (c) 2011 Ben Baron. All rights reserved.
//

#import "SUSServerPlaylistsDAO.h"
#import "FMDatabaseAdditions.h"
#import "DatabaseSingleton.h"
#import "SUSServerPlaylistsLoader.h"

@implementation SUSServerPlaylistsDAO
@synthesize delegate, serverPlaylists, loader;

- (id)initWithDelegate:(NSObject <SUSLoaderDelegate> *)theDelegate
{
    if ((self = [super init]))
    {
        delegate = theDelegate;
    }
    
    return self;
}

- (void)dealloc
{
	loader.delegate = nil;
}

- (FMDatabase *)db
{
    return databaseS.localPlaylistsDb;
}

#pragma mark - Loader Manager Methods

- (void)restartLoad
{
    [self startLoad];
}

- (void)startLoad
{	
    self.loader = [[SUSServerPlaylistsLoader alloc] initWithDelegate:self];
    [self.loader startLoad];
}

- (void)cancelLoad
{
    [self.loader cancelLoad];
	self.loader.delegate = nil;
    self.loader = nil;
}

#pragma mark - Loader Delegate Methods

- (void)loadingFailed:(SUSLoader*)theLoader withError:(NSError *)error
{
	self.loader.delegate = nil;
    self.loader = nil;
	
	if ([self.delegate respondsToSelector:@selector(loadingFailed:withError:)])
	{
		[self.delegate loadingFailed:nil withError:error];
	}
}

- (void)loadingFinished:(SUSLoader*)theLoader
{
	self.serverPlaylists = [NSArray arrayWithArray:loader.serverPlaylists];
	
	self.loader.delegate = nil;
	self.loader = nil;
    
	if ([self.delegate respondsToSelector:@selector(loadingFinished:)])
	{
		[self.delegate loadingFinished:nil];
	}
}

@end
