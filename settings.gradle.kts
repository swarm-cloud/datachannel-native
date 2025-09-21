pluginManagement {
  repositories {
    google()
    gradlePluginPortal()
    mavenCentral()
  }
}
plugins {
  id("org.gradle.toolchains.foojay-resolver-convention") version "0.9.0"
}

dependencyResolutionManagement {
  repositories {
    google()
    mavenCentral()
    mavenLocal()
  }
}

rootProject.name = "data-channel"
include(":data-channel-android")
include(":example:libDC")
include(":example:libWebRTC")
