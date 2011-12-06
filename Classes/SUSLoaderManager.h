//
//  LoaderManager.h
//  iSub
//
//  Created by Ben Baron on 9/24/11.
//  Copyright 2011 Ben Baron. All rights reserved.
//

@protocol SUSLoaderManager <NSObject>

@required
- (id)initWithDelegate:(NSObject <SUSLoaderDelegate> *)theDelegate;
- (void)startLoad;
- (void)cancelLoad;

@end