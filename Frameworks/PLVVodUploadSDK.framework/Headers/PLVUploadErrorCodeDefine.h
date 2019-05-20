//
//  PLVUploadErrorCodeDefine.h
//  PLVVodUploadSDK
//
//  Created by MissYasiky on 2019/4/8.
//  Copyright © 2019 polyv. All rights reserved.
//

#ifndef PLVUploadErrorCodeDefine_h
#define PLVUploadErrorCodeDefine_h

/**
上传错误码 domain
 */
#define PLVClientErrorDomain                    @"com.polyv.upload.polyvClientError"

/**
 上传错误码枚举
 */
typedef NS_ENUM (NSInteger, PLVClientErrorCode) {
    PLVClientErrorCodeLoginFailure = 0, // 登录 SDK 失败（userId、secretKey 为空）
    PLVClientErrorCodeAccountError, // 不得使用公共账号进行上传
    PLVClientErrorCodeGetTokenFailure, // 获取 token 失败
    PLVClientErrorCodeHaventLogin, // 尚未登录 SDK
    PLVClientErrorCodeInitUploadTaskFailure, // 初始化上传任务失败
    PLVClientErrorCodeNoEnoughSpace,  // 云空间不足
    PLVClientErrorCodeOSSErrorCanResumeUpload, // 上传失败，可续传
    PLVClientErrorCodeOSSErrorCannotResumeUpload // 上传失败，不可续传
};

#endif /* PLVUploadErrorCodeDefine_h */
