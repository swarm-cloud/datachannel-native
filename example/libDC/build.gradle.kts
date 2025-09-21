plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.android)
    alias(libs.plugins.compose.compiler)
}

android {
    namespace = "com.cdnbye.dc_perf.libdc"
    compileSdk = Consts.androidCompileSdk
    defaultConfig {
        applicationId = "com.cdnbye.dc_perf.libdc"
        minSdk = 21
        targetSdk = Consts.androidTargetSdk
        versionCode = 1
        versionName = "1.0"

        ndkVersion = Consts.androidNdk
        ndk.abiFilters.addAll(Consts.ndkAbis)
    }
    compileOptions {
        sourceCompatibility = JavaVersion.toVersion(17)//libs.versions.jvm.get().toInt())
        targetCompatibility = JavaVersion.toVersion(17)//libs.versions.jvm.get().toInt())
    }
    buildFeatures {
        compose = true
    }
    packaging {
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
//    implementation(files("$rootDir/libs/data-channel-android-release.aar"))
    implementation(libs.androidx.compose.ui)
    implementation(libs.androidx.compose.ui.tooling)
    implementation(libs.androidx.compose.ui.tooling.preview)
    implementation(libs.androidx.compose.foundation)
    implementation(libs.androidx.compose.material)
    implementation(libs.androidx.activity.compose)
}
