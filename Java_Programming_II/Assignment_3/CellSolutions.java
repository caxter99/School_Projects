import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.Menu;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.control.RadioMenuItem;
import javafx.scene.Scene;
import javafx.scene.layout.TilePane;
import javafx.scene.control.RadioButton;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;

public class CellSolutions extends Application
{

   Label outputLabel;
   int blah;
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   public void start(Stage stage)
   {
      // Stuff to Delete Later
      blah = 0;
      
      // Plan Stuff
      RadioButton planA = new RadioButton("Plan A");
      RadioButton planB = new RadioButton("Plan B");
      RadioButton planC = new RadioButton("Plan C");
      planA.setSelected(true);
      ToggleGroup planToggleGroup = new ToggleGroup();
      planA.setToggleGroup(planToggleGroup);
      planB.setToggleGroup(planToggleGroup);
      planC.setToggleGroup(planToggleGroup);
      planA.setOnAction(event -> calculateTotalBill());
      planB.setOnAction(event -> calculateTotalBill());
      planC.setOnAction(event -> calculateTotalBill());
      
      // Model Stuff
      RadioButton model100 = new RadioButton("Model 100");
      RadioButton model110 = new RadioButton("Model 110");
      RadioButton model200 = new RadioButton("Model 200");
      model100.setSelected(true);
      ToggleGroup modelToggleGroup = new ToggleGroup();
      model100.setToggleGroup(modelToggleGroup);
      model110.setToggleGroup(modelToggleGroup);
      model200.setToggleGroup(modelToggleGroup);
      model100.setOnAction(event -> calculateTotalBill());
      model110.setOnAction(event -> calculateTotalBill());
      model200.setOnAction(event -> calculateTotalBill());
      
      // Extra Options Stuff
      CheckBox insurance = new CheckBox("Model 100");
      CheckBox hotspot = new CheckBox("Model 110");
      insurance.setOnAction(event -> calculateTotalBill());
      hotspot.setOnAction(event -> calculateTotalBill());
      
      // Output Label Stuff
      outputLabel = new Label("Output Label 0");
      
      // Tile Pane Stuff
      TilePane r = new TilePane();
      r.getChildren().add(planA);
      r.getChildren().add(planB);
      r.getChildren().add(planC);
      r.getChildren().add(model100);
      r.getChildren().add(model110);
      r.getChildren().add(model200);
      r.getChildren().add(insurance);
      r.getChildren().add(hotspot);
      r.getChildren().add(outputLabel);
      
      // Scene/Stage Stuff
      Scene seePhoneBillScene = new Scene(r, 500, 500);
      stage.setScene(seePhoneBillScene);
      stage.show();
   }
   
   private void calculateTotalBill()
   {
      blah = blah + 1;
      outputLabel.setText("Output Label " + blah);
   }
}