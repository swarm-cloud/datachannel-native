// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

package com.cdnbye.libdc;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public final class ProxyServer {


    /*package*/ final ProxyServerType mType;

    /*package*/ final String mHostname;

    /*package*/ final short mPort;

    /*package*/ final String mUsername;

    /*package*/ final String mPassword;

    public ProxyServer(
            @NonNull ProxyServerType type,
            @NonNull String hostname,
            short port,
            @Nullable String username,
            @Nullable String password) {
        this.mType = type;
        this.mHostname = hostname;
        this.mPort = port;
        this.mUsername = username;
        this.mPassword = password;
    }

    @NonNull
    public ProxyServerType getType() {
        return mType;
    }

    @NonNull
    public String getHostname() {
        return mHostname;
    }

    public short getPort() {
        return mPort;
    }

    @Nullable
    public String getUsername() {
        return mUsername;
    }

    @Nullable
    public String getPassword() {
        return mPassword;
    }

    @Override
    public String toString() {
        return "ProxyServer{" +
                "mType=" + mType +
                "," + "mHostname=" + mHostname +
                "," + "mPort=" + mPort +
                "," + "mUsername=" + mUsername +
                "," + "mPassword=" + mPassword +
        "}";
    }

}
