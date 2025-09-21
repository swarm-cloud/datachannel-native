buildscript {
    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
}

plugins {
    alias(libs.plugins.android.library) apply false
    alias(libs.plugins.android.application) apply false

    alias(libs.plugins.kotlin.android) apply false

    alias(libs.plugins.nexus.staging)

    alias(libs.plugins.versions)
    alias(libs.plugins.versionUpdate)
}

// ./gradlew versionCatalogUpdate
versionCatalogUpdate {
    sortByKey = false
    keep {
        keepUnusedVersions = true
    }
}

nexusStaging {
    packageGroup = Consts.releaseGroup
    username = getPropString(project, "ossrhUsername")
    password = getPropString(project, "ossrhPassword")
}
