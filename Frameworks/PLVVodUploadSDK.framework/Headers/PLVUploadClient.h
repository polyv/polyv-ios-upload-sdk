//
//  PLVUploadClient.h
//  PLVVodUploadSDK
//
//  Created by MissYasiky on 2019/4/5.
//  Copyright © 2019 polyv. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PLVUploadVideo, PLVUploadParameter;

NS_ASSUME_NONNULL_BEGIN

@protocol PLVUploadClientDelegate <NSObject>

@optional

/**
 SDK 登录失败
 @param error 失败 error （含错误码和 userInfo ）
 */
- (void)uploadClientLoginError:(NSError *)error;

/**
 初始化上传过程中遇到失败
 @param error 失败 error （含错误码和 userInfo ）
 */
- (void)prepareUploadError:(NSError *)error fileURL:(NSURL *)fileURL;

/**
 启动上传任务失败
 @param vid 失败的视频 vid
 */
- (void)startUploadTaskFailure:(NSString *)vid;

/**
 某一个任务被加入等待队列
 @param video 等待上传的任务（ PLVUploadVideo 对象）
 */
- (void)waitingUploadTask:(PLVUploadVideo *)video;

/**
 开始上传某一个任务
 @param video 开始上传的任务（ PLVUploadVideo 对象）
 */
- (void)startUploadTask:(PLVUploadVideo *)video;

/**
 上传结束
 如果成功，error 为 nil
 @param video 上传结束的任务（ PLVUploadVideo 对象）
 @param error 如果上传失败，回传失败的 NSError 对象指针
 */
- (void)didUploadTask:(PLVUploadVideo *)video error:(NSError * __nullable)error;

/**
 上传任务进度变化
 注意：该方法运行在后台线程，非主线程！
 @param vid 视频 vid
 @param progress 上传进度（大于 0 小于 1）
 */
- (void)uploadTask:(NSString *)vid progressChange:(float)progress;

/**
 所有任务上传结束（包括成功或失败，不包含被中止/中断的任务）
 */
- (void)didAllUploadTaskComplete;

@end

/**
 上传控制类
 */
@interface PLVUploadClient : NSObject

/**
 登录 SDK 的用户 ID
 */
@property (nonatomic, copy, readonly) NSString *userId;

/**
 登录 SDK 的用户 secretKey
 */
@property (nonatomic, copy, readonly) NSString *secretKey;

/**
 开启调试日志，默认为 NO
 */
@property (nonatomic, assign) BOOL enableLog;

/**
 PLVUploadClient 单例
 @return PLVUploadClient 单例
 */
+ (instancetype)sharedClient;

/**
 PLVUploadClient 支持多代理
 添加委托代理
 @param delegate 代理
 */
- (void)addDelegate:(id<PLVUploadClientDelegate>)delegate;

/**
 PLVUploadClient 支持多代理
 移除委托代理
 @param delegate 代理
 */
- (void)removeDelegate:(id<PLVUploadClientDelegate>)delegate;

/**
 SDK 登录
 @param userId 用户 ID
 @param secretKey 用户 secretKey
 */
- (void)loginWithUserId:(NSString *)userId secretKey:(NSString *)secretKey;

/**
 上传视频文件
 @param fileURL 视频文件本地 URL
 @return 如果出错，返回一个 NSError 对象，如果没有，返回 nil
 */
- (NSError *)uploadVideoAtFileURL:(NSURL *)fileURL;

/**
 上传视频文件
 @param uploadParameter 参数封装类（包含更多自定义参数）
 @return 如果出错，返回一个 NSError 对象，如果没有，返回 nil
 */
- (NSError *)uploadVideoWithMutipleParameter:(PLVUploadParameter *)uploadParameter;

/**
 中止视频上传
 适用于 status 为 PLVUploadStatusWaiting, PLVUploadStatusUploading 的上传任务
 @param vid 上传任务的 vid
 */
- (void)abortUploadWithVid:(NSString *)vid;

/**
 恢复视频上传
 适用于 status 为 PLVUploadStatusResumable 的上传任务
 @param vid 上传任务的 vid
 @param fileURL 上传文件的 URL
 */
- (void)retryUploadWithVid:(NSString *)vid fileURL:(NSURL *)fileURL;

/**
 返回所有上传中或等待上传的任务
 status 为 PLVUploadStatusWaiting, PLVUploadStatusUploading, PLVUploadStatusResumable
 @return 上传任务数组，数组元素为 PLVUploadVideo 对象
 */
- (NSArray <PLVUploadVideo *>*)allUploadVideos;

/**
 在上传中或等待上传的任务队列中，查找指定 vid 的上传任务
 @param vid 上传任务对应的视频 vid
 @return 上传任务（ PLVUploadVideo 对象）
 */
- (PLVUploadVideo *)videoWithVid:(NSString *)vid;

@end

NS_ASSUME_NONNULL_END
