plugins {
    alias(libs.plugins.android.library)
    id("convention.publication")
}

android {
    compileSdk = Consts.androidCompileSdk
    ndkVersion = Consts.androidNdk
    namespace = Consts.androidNS

    defaultConfig {
        minSdk = Consts.androidMinSdk
        targetSdk = Consts.androidTargetSdk

        ndkVersion = Consts.androidNdk
        ndk.abiFilters.addAll(Consts.ndkAbis)

        sourceSets {
            getByName("main") {
                java.srcDirs(
                    "src/main/java",
                    "${rootProject.projectDir}/generated-src/java"
                )
            }
        }

        externalNativeBuild {
            cmake {
                arguments.addAll(
                    listOf(
                        "-DANDROID_STL=c++_shared",
                        "-DNO_WEBSOCKET=ON",
                        "-DNO_MEDIA=ON",
                        "-DNO_EXAMPLES=ON",
                        "-DNO_TESTS=ON"
                    )
                )
                targets("datachannel-static", "datachannel_wrapper")
            }
        }

        consumerProguardFiles("proguard-consumer-rules.pro")
    }

    compileOptions {
        sourceCompatibility = JavaVersion.toVersion(libs.versions.jvm.get().toInt())
        targetCompatibility = JavaVersion.toVersion(libs.versions.jvm.get().toInt())
    }

    packaging {
        resources {
            excludes += "**/libcrypto.so"
            excludes += "**/libssl.so"
        }
    }

    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
        }
    }

    externalNativeBuild {
        cmake {
            path = file("../src/CMakeLists.txt")
            version = "3.22.1"
        }
    }

//  buildFeatures {
//    prefab = true
//  }
}

dependencies {
    implementation(libs.androidx.annotation)
    // implementation("com.android.ndk.thirdparty:openssl:_")
}