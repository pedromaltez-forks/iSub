//
//  ArtistUITableViewCell.h
//  iSub
//
//  Created by Ben Baron on 5/7/10.
//  Copyright 2010 Ben Baron. All rights reserved.
//

#import "CustomUITableViewCell.h"

@class Artist;

@interface ArtistUITableViewCell : CustomUITableViewCell 

@property (strong) UIScrollView *artistNameScrollView;
@property (strong) UILabel *artistNameLabel;

@property (strong) Artist *myArtist;

@end
