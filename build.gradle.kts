buildscript {
    repositories {
        gradlePluginPortal()
        google()
        mavenCentral()
    }
}

plugins {
    id("io.codearte.nexus-staging")
}

nexusStaging {
    packageGroup = Consts.releaseGroup
    username = getPropString(project, "ossrhUsername")
    password = getPropString(project, "ossrhPassword")
}
