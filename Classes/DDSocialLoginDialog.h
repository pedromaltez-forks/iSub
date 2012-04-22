//
//  DDSocialLoginDialog.h
//
//  Created by digdog on 6/6/10.
//  Copyright 2010 Ching-Lan 'digdog' HUANG and digdog software. All rights reserved.
//  http://digdog.tumblr.com
//
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files (the
//  "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so, subject to
//  the following conditions:
//   
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//   
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

/*
 * Copyright 2009 Facebook
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "DDSocialDialog.h"

@protocol DDSocialLoginDialogDelegate;

@interface DDSocialLoginDialog : DDSocialDialog <UITableViewDelegate, UITableViewDataSource, UITextFieldDelegate> {
@private
	NSString *username_;
	NSString *password_;
	
	UITextField *usernameField_;
	UITextField *passwordField_;
	UITableView *tableView_;
	
	id <DDSocialLoginDialogDelegate> __unsafe_unretained delegate_;
}

@property (nonatomic, readonly, copy) NSString *username;
@property (nonatomic, readonly, copy) NSString *password;
@property (nonatomic, unsafe_unretained) id <DDSocialLoginDialogDelegate> delegate;

- (id)initWithDelegate:(id)delegate theme:(DDSocialDialogTheme)theme;
@end

@protocol DDSocialLoginDialogDelegate <DDSocialDialogDelegate>
@required
- (void)socialDialogDidSucceed:(DDSocialLoginDialog *)socialLoginDialog; // Use socialLoginDialog.username and socialLoginDialog.password 
@end