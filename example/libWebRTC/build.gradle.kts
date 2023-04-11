import de.fayard.refreshVersions.core.versionFor

plugins {
    id("com.android.application")
    kotlin("android")
}

android {
    namespace = "com.cdnbye.dc_perf.libwebrtc"
    compileSdk = Consts.androidCompileSdk
    defaultConfig {
        applicationId = "com.cdnbye.dc_perf.libwebrtc"
        minSdk = 21
        targetSdk = Consts.androidTargetSdk
        versionCode = 1
        versionName = "1.0"

        ndkVersion = Consts.androidNdk
        ndk.abiFilters.addAll(Consts.ndkAbis)
    }
    buildFeatures {
        compose = true
    }
    composeOptions {
        kotlinCompilerExtensionVersion = versionFor(AndroidX.compose.compiler)
    }
    packagingOptions {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
        }
    }
}

dependencies {
    implementation(files("$rootDir/libs/webrtc.aar"))
    implementation(AndroidX.compose.ui)
    implementation(AndroidX.compose.ui.tooling)
    implementation(AndroidX.compose.ui.toolingPreview)
    implementation(AndroidX.compose.foundation)
    implementation(AndroidX.compose.material)
    implementation(AndroidX.activity.compose)
}
