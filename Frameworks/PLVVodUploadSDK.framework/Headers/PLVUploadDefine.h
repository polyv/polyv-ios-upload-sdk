//
//  PLVUploadDefine.h
//  PLVVodUploadSDK
//
//  Created by MissYasiky on 2019/5/14.
//  Copyright © 2019 polyv. All rights reserved.
//

#import "PLVUploadClient.h"

#ifndef PLVUploadDefine_h
#define PLVUploadDefine_h

#define PLVUploadLog(format, ...)    if ([PLVUploadClient sharedClient].enableLog)    {NSLog((@"[PLV_UPLOAD_SDK] " format), ##__VA_ARGS__);}

#endif /* PLVUploadDefine_h */
