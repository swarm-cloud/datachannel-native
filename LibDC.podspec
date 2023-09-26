Pod::Spec.new do |s|
  s.name = 'LibDC'
  s.version = '1.0.8'
  s.license = 'MIT'
  s.summary = 'C++ WebRTC Data Channels for mobile'
  s.homepage = 'https://github.com/swarm-cloud/datachannel-native'
  s.authors = { 'SwarmCloud' => 'cdnbye@gmail.com' }

  s.ios.deployment_target = '13.0'
  s.osx.deployment_target = '10.15'
  s.tvos.deployment_target = '13.0'

  s.swift_versions = ['5']

  s.source        = { :http => 'https://cdn.swarmcloud.net/apple/libDC/v1.0.8/datachannel_wrapper.xcframework.zip' }

  s.vendored_frameworks = 'datachannel_wrapper.xcframework'

end
