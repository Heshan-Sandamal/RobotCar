/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package robotcar;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Heshan Sandamal
 */
public class RobotCar {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            NetworkConnector.ConnectToServer();
            //robotController.write();
        } catch (IOException ex) {
            Logger.getLogger(RobotCar.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
