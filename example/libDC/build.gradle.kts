import de.fayard.refreshVersions.core.versionFor

plugins {
    id("com.android.application")
    kotlin("android")
}

android {
    namespace = "com.cdnbye.dc_perf.libdc"
    compileSdk = Consts.androidCompileSdk
    defaultConfig {
        applicationId = "com.cdnbye.dc_perf.libdc"
        minSdk = Consts.androidMinSdk
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
    implementation(project(":data-channel-android"))
    implementation(AndroidX.compose.ui)
    implementation(AndroidX.compose.ui.tooling)
    implementation(AndroidX.compose.ui.toolingPreview)
    implementation(AndroidX.compose.foundation)
    implementation(AndroidX.compose.material)
    implementation(AndroidX.activity.compose)
}
