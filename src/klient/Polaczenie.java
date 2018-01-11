/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package klient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.channels.SocketChannel;
import java.util.Observable;

/**
 *
 * @author rootmistrz
 */
public class Polaczenie extends Observable {

    private Socket gniazdo;

    public void inicjujGniazdo(String adres, int port) throws IOException {
        setGniazdo(new Socket(adres, port));
    }

    public void zamknijPolaczenie() {
        try {
            getGniazdo().close();
        } catch (IOException ex) {
            notifyObservers(ex);
        }
    }

    /**
     * @return the gniazdo
     */
    public Socket getGniazdo() {
        return gniazdo;
    }

    /**
     * @param gniazdo the gniazdo to set
     */
    public void setGniazdo(Socket gniazdo) {
        this.gniazdo = gniazdo;
    }

}
