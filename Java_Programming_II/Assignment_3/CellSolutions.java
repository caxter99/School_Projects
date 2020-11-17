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
import javafx.scene.layout.VBox;

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
      VBox planVBox = new VBox();
      planVBox.getChildren().add(planA);
      planVBox.getChildren().add(planB);
      planVBox.getChildren().add(planC);
      
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
      VBox modelVBox = new VBox();
      modelVBox.getChildren().add(model100);
      modelVBox.getChildren().add(model110);
      modelVBox.getChildren().add(model200);
      
      // Extra Options Stuff
      CheckBox insurance = new CheckBox("Phone Replacement Insurance");
      CheckBox hotspot = new CheckBox("WiFi HotSpot Capability");
      insurance.setOnAction(event -> calculateTotalBill());
      hotspot.setOnAction(event -> calculateTotalBill());
      VBox extraOptionsVBox = new VBox();
      extraOptionsVBox.getChildren().add(insurance);
      extraOptionsVBox.getChildren().add(hotspot);
      
      // Output Label Stuff
      outputLabel = new Label("Output Label 0");
      
      // Tile Pane Stuff
      TilePane tile = new TilePane();
      tile.getChildren().add(planVBox);
      tile.getChildren().add(modelVBox);
      tile.getChildren().add(extraOptionsVBox);
      tile.getChildren().add(outputLabel);
      
      // Scene/Stage Stuff
      Scene seePhoneBillScene = new Scene(tile, 500, 500);
      stage.setScene(seePhoneBillScene);
      stage.show();
   }
   
   private void buildDataPlans()
   {
      // to do
   }
   
   private void calculateTotalBill()
   {
      blah = blah + 1;
      outputLabel.setText("Output Label " + blah);
   }
}