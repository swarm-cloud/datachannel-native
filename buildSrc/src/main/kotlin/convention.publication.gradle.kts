// credit: https://dev.to/kotlin/how-to-build-and-publish-a-kotlin-multiplatform-library-going-public-4a8k
import java.util.Properties

plugins {
  `maven-publish`
  signing
}

ext["signing.keyId"] = getPropString(project, "signing.keyId")
ext["signing.password"] = getPropString(project, "signing.password")
ext["signing.secretKeyRingFile"] = getPropString(project, "signing.secretKeyRingFile")

val javadocJar by tasks.registering(Jar::class) {
  archiveClassifier.set("javadoc")
}

publishing {
  // Configure maven central repository
  repositories {
    maven {
      name = "sonatype"
      setUrl("https://s01.oss.sonatype.org/service/local/staging/deploy/maven2/")
      credentials {
        username = getPropString(project, "ossrhUsername")
        password = getPropString(project, "ossrhPassword")
      }
    }
  }

  // Configure all publications
  publications.withType<MavenPublication> {
    // Stub javadoc.jar artifact
    artifact(javadocJar.get())

    // Provide artifacts information requited by Maven Central
    pom {
      name.set(project.name)
      description.set(getPropString(project, "artifact.desc"))
      url.set(getPropString(project, "artifact.url"))

      licenses {
        license {
          name.set("MIT")
          url.set("https://opensource.org/licenses/MIT")
        }
      }
      developers {
        developer {
          id.set(getPropString(project, "developer.id"))
          name.set(getPropString(project, "developer.name"))
          email.set(getPropString(project, "developer.email"))
        }
      }
      scm {
        url.set(getPropString(project, "artifact.url"))
      }
    }
  }
}

// Signing artifacts. Signing.* extra properties values will be used
signing {
  sign(publishing.publications)
}

group = Consts.releaseGroup
version = Consts.releaseVersion
