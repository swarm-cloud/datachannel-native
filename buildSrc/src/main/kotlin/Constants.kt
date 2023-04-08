object Consts {
  const val agp = "7.3.0"

  const val kotlin = "1.8.0"

  const val androidCompileSdk = 33
  const val androidMinSdk = 21
  const val androidTargetSdk = 33
  const val androidNdk = "23.1.7779620"
  val ndkAbis = arrayOf("armeabi-v7a", "arm64-v8a", "x86", "x86_64")

  const val iosDeploymentTarget = "14.0"

  const val releaseGroup = "com.piasy"
  const val releaseName = "kmp-xlog"
  const val releaseVersion = "1.1.0"

  val androidNS = "$releaseGroup.${releaseName.replace('-', '_')}"
}
