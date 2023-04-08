pluginManagement {
  repositories {
    google()
    gradlePluginPortal()
    mavenCentral()
  }

  plugins {
    // See https://jmfayard.github.io/refreshVersions
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
