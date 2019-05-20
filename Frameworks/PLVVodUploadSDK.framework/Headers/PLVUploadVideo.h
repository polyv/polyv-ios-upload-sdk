//
//  PLVUploadVideo.h
//  PLVVodUploadSDK
//
//  Created by MissYasiky on 2019/4/11.
//  Copyright © 2019 polyv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PLVUploadErrorCodeDefine.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^PLVUploadProgressBlock) (float progress);

/**
 视频上传状态
 - PLVUploadStatusWaiting: 超过最大并发数等待上传中
 - PLVUploadStatusUploading: 上传中
 - PLVUploadStatusResumable: 上传中断，可续传
 - PLVUploadStatusFailure: 上传失败，不可续传
 - PLVUploadStatusAborted: 上传任务被中止，不可续传
 - PLVUploadStatusComplete: 上传成功
 */
typedef NS_ENUM(NSInteger, PLVUploadStatus) {
    PLVUploadStatusWaiting = 0,
    PLVUploadStatusUploading,
    PLVUploadStatusResumable,
    PLVUploadStatusFailure,
    PLVUploadStatusAborted,
    PLVUploadStatusComplete
};

/**
 上传任务模型
 */
@interface PLVUploadVideo : NSObject

/**
 上传任务的 vid，后台对视频上传任务的唯一标识
 */
@property (nonatomic, copy) NSString *vid;

/**
 视频上传状态
 */
@property (nonatomic, assign) PLVUploadStatus status;

/**
 视频文件本地 URL
 */
@property (nonatomic, strong) NSURL *fileURL;

/**
 视频文件名
 */
@property (nonatomic, copy) NSString *fileName;

/**
 视频大小
 */
@property (nonatomic, assign) NSInteger fileSize;

/**
 视频上传进度（ progress 大于 0，小于 1 ）
 */
@property (nonatomic, assign) float progress;

/**
 视频上传进度回调 block（该 block 运行在后台线程，非主线程！）
 */
@property (nonatomic, copy) PLVUploadProgressBlock uploadProgress;

@end

NS_ASSUME_NONNULL_END
