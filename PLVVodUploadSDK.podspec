#
#  Be sure to run `pod spec lint PolyvUploadSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see https://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |spec|

  spec.name         = "PLVVodUploadSDK"
  spec.version      = "0.1.1"
  spec.summary      = "保利威视视频上传 iOS SDK."
  spec.description  = <<-DESC
  PolyvUploadSDK 是保利威视公司的视频上传 iOS SDK，
  提供可断点续传的视频上传功能。
                   DESC

  spec.homepage     = "https://github.com/polyv/polyv-ios-upload-sdk"

  spec.license      = "MIT"

  spec.author             = { "MissYasiky" => "gzxieyunjia@gmail.com" }
  spec.requires_arc = true
  spec.platform = :ios, "8.0"
  spec.source       = { :git => "https://github.com/polyv/polyv-ios-upload-sdk.git", :tag => "#{spec.version}" }
  spec.vendored_frameworks = "Frameworks/PLVVodUploadSDK.framework"

  # ――― Source Code ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  CocoaPods is smart about how it includes source code. For source files
  #  giving a folder will include any swift, h, m, mm, c & cpp files.
  #  For header files it will include any header in the folder.
  #  Not including the public_header_files will make all headers public.
  #

  # spec.source_files  = "Classes", "Classes/**/*.{h,m}"
  # spec.exclude_files = "Classes/Exclude"
  # spec.public_header_files = "Classes/**/*.h"


  # ――― Project Linking ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  Link your library with frameworks, or libraries. Libraries do not include
  #  the lib prefix of their name.
  #

  # spec.framework  = "SomeFramework"
  # spec.frameworks = "CoreTelephony", "SystemConfiguration"

  # spec.library   = "iconv"
  # spec.libraries = "iconv", "xml2"
  spec.dependency "AliyunOSSiOS", '~> 2.10.7'


end
