#! /usr/bin/env bash
set -eu
shopt -s nullglob

export DEVELOPER_DIR=/Applications/Xcode_14.1.app/Contents/Developer/

# Locate the script file.  Cross symlinks if necessary.
loc="$0"
while [ -h "$loc" ]; do
    ls=`ls -ld "$loc"`
    link=`expr "$ls" : '.*-> \(.*\)$'`
    if expr "$link" : '/.*' > /dev/null; then
        loc="$link"  # Absolute link
    else
        loc="`dirname "$loc"`/$link"  # Relative link
    fi
done
base_dir=$(cd "`dirname "$loc"`" && pwd)

temp_out="$base_dir/djinni-output-temp"

in="$base_dir/idl/libdc.djinni"

cpp_out="$base_dir/generated-src/cpp"
jni_out="$base_dir/generated-src/jni"
objc_out="$base_dir/generated-src/objc"
java_out="$base_dir/generated-src/java/com/cdnbye/libdc"

java_package="com.cdnbye.libdc"

gen_stamp="$temp_out/gen.stamp"

if [ $# -eq 0 ]; then
    # Normal build.
    true
elif [ $# -eq 1 ]; then
    command="$1"; shift
    if [ "$command" != "clean" ]; then
        echo "Unexpected argument: \"$command\"." 1>&2
        exit 1
    fi
    for dir in "$temp_out" "$cpp_out" "$jni_out" "$java_out"; do
        if [ -e "$dir" ]; then
            echo "Deleting \"$dir\"..."
            rm -r "$dir"
        fi
    done
    exit
fi

# Build djinni
export BAZEL_EXECUTABLE="bazel --output_base=$HOME/.cache/bazel --output_user_root=$HOME/.cache/bazel_install"
"$base_dir/djinni/src/build.sh"

[ ! -e "$temp_out" ] || rm -r "$temp_out"
"$base_dir/djinni/src/run-assume-built" \
    --java-out "$temp_out/java" \
    --java-package $java_package \
    --java-class-access-modifier "public" \
    --java-gen-interface true \
    --java-nullable-annotation "androidx.annotation.Nullable" \
    --java-nonnull-annotation "androidx.annotation.NonNull" \
    --ident-java-field mFooBar \
    \
    --cpp-out "$temp_out/cpp" \
    --cpp-namespace libdc \
    --ident-cpp-enum-type foo_bar \
    \
    --jni-out "$temp_out/jni" \
    --ident-jni-class NativeFooBar \
    --ident-jni-file NativeFooBar \
    \
    --objc-out "$temp_out/objc" \
    --objcpp-out "$temp_out/objc" \
    --objc-type-prefix DC \
    --objc-swift-bridging-header "LibDC-Bridging-Header" \
    \
    --idl "$in"

# Copy changes from "$temp_output" to final dir.

mirror() {
    local prefix="$1" ; shift
    local src="$1" ; shift
    local dest="$1" ; shift
    mkdir -p "$dest"
    rsync -r --delete --checksum --itemize-changes "$src"/ "$dest" | sed "s/^/[$prefix]/"
}

echo "Copying generated code to final directories..."
mirror "cpp" "$temp_out/cpp" "$cpp_out"
mirror "java" "$temp_out/java" "$java_out"
mirror "jni" "$temp_out/jni" "$jni_out"
mirror "objc" "$temp_out/objc" "$objc_out"

cp djinni/support-lib/java/com/snapchat/djinni/NativeObjectManager.java \
    data-channel-android/src/main/java/com/snapchat/djinni/NativeObjectManager.java

date > "$gen_stamp"

echo "djinni completed."
