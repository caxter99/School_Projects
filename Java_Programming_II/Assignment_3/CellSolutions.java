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

   Label monthlyCostLabel;
   Label initialCostLabel;
   Label totalCostLabel;
   Cart cart;
   final int PLAN_A_NUM = 1;
   final int PLAN_B_NUM = 2;
   final int PLAN_C_NUM = 3;
   final int MODEL_100_NUM = 1;
   final int MODEL_110_NUM = 2;
   final int MODEL_200_NUM = 3;
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   public void start(Stage stage)
   {
      cart = new Cart();
      TilePane tile = buildTilePane();
      calculateTotalBill();
      
      Scene seeBillScene = new Scene(tile, 500, 500);
      stage.setScene(seeBillScene);
      
      stage.show();
   }
   
   private TilePane buildTilePane()
   {
      VBox planVBox = buildPlansVBox();
      VBox modelVBox = buildModelsVBox();
      VBox extraOptionsVBox = buildExtraOptionsVBox();
      initialCostLabel = new Label("");
      monthlyCostLabel = new Label("");
      totalCostLabel = new Label("");
      
      TilePane tilePane = new TilePane();
      tilePane.getChildren().add(planVBox);
      tilePane.getChildren().add(modelVBox);
      tilePane.getChildren().add(extraOptionsVBox);
      tilePane.getChildren().add(initialCostLabel);
      tilePane.getChildren().add(monthlyCostLabel);
      tilePane.getChildren().add(totalCostLabel);
      
      return tilePane;
   }
   
   private VBox buildPlansVBox()
   {
      RadioButton planA = new RadioButton("Plan A");
      RadioButton planB = new RadioButton("Plan B");
      RadioButton planC = new RadioButton("Plan C");
      planA.setSelected(true);
      
      ToggleGroup planToggleGroup = new ToggleGroup();
      planA.setToggleGroup(planToggleGroup);
      planB.setToggleGroup(planToggleGroup);
      planC.setToggleGroup(planToggleGroup);
      
      planA.setOnAction(event -> updatePlan(PLAN_A_NUM));
      planB.setOnAction(event -> updatePlan(PLAN_B_NUM));
      planC.setOnAction(event -> updatePlan(PLAN_C_NUM));
      
      VBox planVBox = new VBox();
      planVBox.getChildren().add(planA);
      planVBox.getChildren().add(planB);
      planVBox.getChildren().add(planC);
      
      return planVBox;
   }
   
   private VBox buildModelsVBox()
   {
      RadioButton model100 = new RadioButton("Model 100");
      RadioButton model110 = new RadioButton("Model 110");
      RadioButton model200 = new RadioButton("Model 200");
      model100.setSelected(true);
      
      ToggleGroup modelToggleGroup = new ToggleGroup();
      model100.setToggleGroup(modelToggleGroup);
      model110.setToggleGroup(modelToggleGroup);
      model200.setToggleGroup(modelToggleGroup);
      
      model100.setOnAction(event -> updatePhoneModel(MODEL_100_NUM));
      model110.setOnAction(event -> updatePhoneModel(MODEL_110_NUM));
      model200.setOnAction(event -> updatePhoneModel(MODEL_200_NUM));
      
      VBox modelVBox = new VBox();
      modelVBox.getChildren().add(model100);
      modelVBox.getChildren().add(model110);
      modelVBox.getChildren().add(model200);
      
      return modelVBox;
   }
   
   private VBox buildExtraOptionsVBox()
   {
      CheckBox insurance = new CheckBox("Phone Replacement Insurance");
      CheckBox hotspot = new CheckBox("WiFi HotSpot Capability");
      
      insurance.setOnAction(event -> calculateTotalBill());
      hotspot.setOnAction(event -> calculateTotalBill());
      
      VBox extraOptionsVBox = new VBox();
      extraOptionsVBox.getChildren().add(insurance);
      extraOptionsVBox.getChildren().add(hotspot);
      
      return extraOptionsVBox;
   }
   
   private void updatePlan(int planNum)
   {
      cart.setPlan(planNum);
      
      calculateTotalBill();
   }
   
   private void updatePhoneModel(int phoneModelNum)
   {
      cart.setPhoneModel(phoneModelNum);
      
      calculateTotalBill();
   }
   
   private void updateHasInsurance(boolean insurance)
   {
      cart.setHasInsurance(insurance);
      
      calculateTotalBill();
   }
   
   private void setHasHotspot(boolean hotspot)
   {
      cart.setHasHotspot(hotspot);
      
      calculateTotalBill();
   }
   
   private void calculateTotalBill()
   {
      initialCostLabel.setText("Initial Cost: " + cart.getInitialCost());
      monthlyCostLabel.setText("Monthly Cost: " + cart.getMonthlyCost());
      totalCostLabel.setText("Total Cost (Monthly + Initial): " + cart.getTotalCost());
   }
}