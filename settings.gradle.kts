pluginManagement {
  repositories {
    google()
    gradlePluginPortal()
    mavenCentral()
  }

  plugins {
    // See https://jmfayard.github.io/refreshVersions
    // ./gradlew refreshVersionsMigrate --mode=VersionsPropertiesOnly
    // ./gradlew refreshVersions
    id("de.fayard.refreshVersions") version "0.51.0"
  }
}

plugins {
  id("de.fayard.refreshVersions")
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
