/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package robotcar;

import java.io.IOException;

/**
 *
 * @author Heshan Sandamal
 */
public class UserController {

    private double leftSonarVal;
    private double centerSonarVal;
    private double RIghtSonarVal;

    private double angle=0;
    

    public void TurnLeft() throws IOException {
        angle--;
        NetworkConnector.write("l");
        
    }

    public void TurnRight() throws IOException {
        angle++;
        NetworkConnector.write("r");
    }

    public void forward() throws IOException {
        NetworkConnector.write("f");
    }

    public void backward() throws IOException {
         NetworkConnector.write("b");
    }
    
    public void stop() throws IOException{
        NetworkConnector.write("s");
    }

    public void setCenterSonarVal(double centerSonarVal) {
        this.centerSonarVal = centerSonarVal;
        
        //call gui method to set center sonar value
        
    }

    public void setLeftSonarVal(double leftSonarVal) {
        this.leftSonarVal = leftSonarVal;
        
        //call gui method to set left sonar value
    }

    public void setRIghtSonarVal(double RIghtSonarVal) {
        this.RIghtSonarVal = RIghtSonarVal;
        
        //call gui method to set right sonar value
    }




}
