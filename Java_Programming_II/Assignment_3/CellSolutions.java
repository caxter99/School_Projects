import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.Menu;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.control.RadioMenuItem;
import javafx.scene.Scene;
import javafx.scene.layout.TilePane;
import javafx.scene.control.RadioButton;
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
      
      // Output Label Stuff
      outputLabel = new Label("Output Label");
      
      // Adding Stuff to the Tile Pane
      TilePane r = new TilePane();
      r.getChildren().add(planA);
      r.getChildren().add(planB);
      r.getChildren().add(planC);
      r.getChildren().add(outputLabel);
      
      // Scene/Stage Stuff
      Scene seePhoneBillScene = new Scene(r, 500, 500);
      stage.setScene(seePhoneBillScene);
      stage.show();
   }
   
   private void calculateTotalBill()
   {
      blah = blah + 1;
      outputLabel.setText("Yo!" + blah);
   }
}