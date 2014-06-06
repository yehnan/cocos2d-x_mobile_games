/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.jasoet.chat.util;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 *
 * @author jasoet
 */
public final class EncriptionUtil {

    public static String MD5MySQL(String input) {
        String result = input;
        if (input != null) {
            try {
                MessageDigest md = MessageDigest.getInstance("MD5"); //or "SHA-1"
                md.update(input.getBytes());
                BigInteger hash = new BigInteger(1, md.digest());
                result = hash.toString(16);
                if ((result.length() % 2) != 0) {
                    result = "0" + result;
                }
            } catch (NoSuchAlgorithmException ex) {
                ex.printStackTrace();
            }
        }
        return result;
    }
}
