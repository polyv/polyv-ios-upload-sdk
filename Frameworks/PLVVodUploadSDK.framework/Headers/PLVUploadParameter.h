//
//  PLVUploadParameter.h
//  PLVVodUploadSDK
//
//  Created by MissYasiky on 2019/5/16.
//  Copyright © 2019 polyv. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 初始化视频上传任务时的参数封装类
 */
@interface PLVUploadParameter : NSObject

/**
 待上传的视频文件的本地存储 URL
 */
@property (nonatomic, strong) NSURL *fileURL;

/**
 上传目录分类 ID，默认为根目录（ID 为 1）
 */
@property (nonatomic, assign) long long catalogId;

/**
 是否录屏，默认为否
 */
@property (nonatomic, assign) BOOL screenRecord;

/**
 是否保持源文件，默认为否
 */
@property (nonatomic, assign) BOOL keepSource;

/**
 待上传的视频文件描述，可选，不传默认为空
 */
@property (nonatomic, copy) NSString * __nullable videoDescription;

/**
 待上传的视频文件标签，可选，不传默认为空
 */
@property (nonatomic, copy) NSString * __nullable videoTag;

@end

NS_ASSUME_NONNULL_END
