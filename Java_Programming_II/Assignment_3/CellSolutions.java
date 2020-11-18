import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.ToggleGroup;
import javafx.scene.Scene;
import javafx.scene.layout.TilePane;
import javafx.scene.control.RadioButton;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.TextField;

public class CellSolutions extends Application
{
   final int PLAN_A_NUM = 1;
   final int PLAN_B_NUM = 2;
   final int PLAN_C_NUM = 3;
   final int MODEL_100_NUM = 1;
   final int MODEL_110_NUM = 2;
   final int MODEL_200_NUM = 3;
   final int APPLICATION_WIDTH = 630;
   final int APPLICATION_HEIGHT = 360;
   final String TITLE = "Cell Solutions";
   Cart cart;
   Label phoneSubTotalLabel;
   Label phoneTaxLabel;
   Label phoneCostLabel;
   Label optionsCostLabel;
   Label planCostLabel;
   Label monthlyCostLabel;
   Label totalCostLabel;
   TextField phoneSubTotalTextField;
   TextField phoneTaxTextField;
   TextField phoneCostTextField;
   TextField optionsCostTextField;
   TextField planCostTextField;
   TextField monthlyCostTextField;
   TextField totalCostTextField;
   CheckBox insuranceCheckBox;
   CheckBox hotspotCheckBox;
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   public void start(Stage stage)
   {
      cart = new Cart();
      TilePane tile = buildTilePane();
      calculateTotalBill();
      
      Scene seeBillScene = new Scene(tile, APPLICATION_WIDTH, APPLICATION_HEIGHT);
      stage.setScene(seeBillScene);
      stage.setTitle(TITLE);
      
      stage.show();
   }
   
   private TilePane buildTilePane()
   {
      HBox selectionHBox = buildSelectionHBox();
      HBox costHBox = buildCostHBox();
      
      TilePane tilePane = new TilePane();
      tilePane.getChildren().add(selectionHBox);
      tilePane.getChildren().add(costHBox);
      
      return tilePane;
   }
   
   private HBox buildSelectionHBox()
   {
      VBox planVBox = buildPlansVBox();
      VBox modelVBox = buildModelsVBox();
      VBox optionsVBox = buildExtraOptionsVBox();
      
      HBox selectionHBox = new HBox();
      selectionHBox.setPadding(new Insets(0, 5, 0, 5));
      selectionHBox.setSpacing(25);
      selectionHBox.setAlignment(Pos.CENTER_LEFT);
      
      selectionHBox.getChildren().add(planVBox);
      selectionHBox.getChildren().add(modelVBox);
      selectionHBox.getChildren().add(optionsVBox);
      
      return selectionHBox;
   }
   
   private HBox buildCostHBox()
   {
      VBox costLabelsVBox = buildCostLabelsVBox();
      VBox costTextFieldsVBox = buildCostTextFieldsVBox();
      
      HBox costHBox = new HBox();
      costHBox.setAlignment(Pos.TOP_LEFT);
      
      costHBox.getChildren().add(costLabelsVBox);
      costHBox.getChildren().add(costTextFieldsVBox);
      
      return costHBox;
      
   }
   
   private VBox buildCostLabelsVBox()
   {
      phoneSubTotalLabel = new Label("Phone Subtotal:");
      phoneTaxLabel = new Label("Phone Tax:");
      phoneCostLabel = new Label("Phone Total:");
      optionsCostLabel = new Label("Extra Options (Monthly):");
      planCostLabel = new Label("Plan Cost (Monthly):");
      monthlyCostLabel = new Label("Total Monthly Cost:");
      totalCostLabel = new Label("Total Cost (Total Monthly + Total Phone):");
      
      VBox costLabelsVBox = new VBox();
      costLabelsVBox.setPadding(new Insets(0, 5, 0, 0));
      costLabelsVBox.setSpacing(9);
      costLabelsVBox.setAlignment(Pos.TOP_RIGHT);
      
      costLabelsVBox.getChildren().add(phoneSubTotalLabel);
      costLabelsVBox.getChildren().add(phoneTaxLabel);
      costLabelsVBox.getChildren().add(phoneCostLabel);
      costLabelsVBox.getChildren().add(optionsCostLabel);
      costLabelsVBox.getChildren().add(planCostLabel);
      costLabelsVBox.getChildren().add(monthlyCostLabel);
      costLabelsVBox.getChildren().add(totalCostLabel);
      
      return costLabelsVBox;
   }
   
   private VBox buildCostTextFieldsVBox()
   {
      phoneSubTotalTextField = new TextField("");
      phoneTaxTextField = new TextField("");
      phoneCostTextField = new TextField("");
      optionsCostTextField = new TextField("");
      planCostTextField = new TextField("");
      monthlyCostTextField = new TextField("");
      totalCostTextField = new TextField("");
      
      phoneSubTotalTextField.setEditable(false);
      phoneTaxTextField.setEditable(false);
      phoneCostTextField.setEditable(false);
      optionsCostTextField.setEditable(false);
      planCostTextField.setEditable(false);
      monthlyCostTextField.setEditable(false);
      totalCostTextField.setEditable(false);
      
      VBox costTextFieldsVBox = new VBox();
      costTextFieldsVBox.setAlignment(Pos.TOP_LEFT);
      
      costTextFieldsVBox.getChildren().add(phoneSubTotalTextField);
      costTextFieldsVBox.getChildren().add(phoneTaxTextField);
      costTextFieldsVBox.getChildren().add(phoneCostTextField);
      costTextFieldsVBox.getChildren().add(optionsCostTextField);
      costTextFieldsVBox.getChildren().add(planCostTextField);
      costTextFieldsVBox.getChildren().add(monthlyCostTextField);
      costTextFieldsVBox.getChildren().add(totalCostTextField);
      
      return costTextFieldsVBox;
   }
   
   private VBox buildPlansVBox()
   {
      RadioButton planARadioButton = new RadioButton("8 GB for $45 per month");
      RadioButton planBRadioButton = new RadioButton("16 GB for $65 per month");
      RadioButton planCRadioButton = new RadioButton("20 GB for $99 per month");
      Label titleLabel = new Label("Select a Plan:");
      planARadioButton.setSelected(true);
      
      ToggleGroup planToggleGroup = new ToggleGroup();
      planARadioButton.setToggleGroup(planToggleGroup);
      planBRadioButton.setToggleGroup(planToggleGroup);
      planCRadioButton.setToggleGroup(planToggleGroup);
      
      planARadioButton.setOnAction(event -> updatePlan(PLAN_A_NUM));
      planBRadioButton.setOnAction(event -> updatePlan(PLAN_B_NUM));
      planCRadioButton.setOnAction(event -> updatePlan(PLAN_C_NUM));
      
      VBox planVBox = new VBox();
      planVBox.getChildren().add(titleLabel);
      planVBox.getChildren().add(planARadioButton);
      planVBox.getChildren().add(planBRadioButton);
      planVBox.getChildren().add(planCRadioButton);
      
      return planVBox;
   }
   
   private VBox buildModelsVBox()
   {
      RadioButton model100RadioButton = new RadioButton("Model 100 for $299.95");
      RadioButton model110RadioButton = new RadioButton("Model 110 for $399.95");
      RadioButton model200RadioButton = new RadioButton("Model 200 for $499.95");
      Label titleLabel = new Label("Select a Phone Model:");
      model100RadioButton.setSelected(true);
      
      ToggleGroup modelToggleGroup = new ToggleGroup();
      model100RadioButton.setToggleGroup(modelToggleGroup);
      model110RadioButton.setToggleGroup(modelToggleGroup);
      model200RadioButton.setToggleGroup(modelToggleGroup);
      
      model100RadioButton.setOnAction(event -> updatePhoneModel(MODEL_100_NUM));
      model110RadioButton.setOnAction(event -> updatePhoneModel(MODEL_110_NUM));
      model200RadioButton.setOnAction(event -> updatePhoneModel(MODEL_200_NUM));
      
      VBox modelVBox = new VBox();
      modelVBox.getChildren().add(titleLabel);
      modelVBox.getChildren().add(model100RadioButton);
      modelVBox.getChildren().add(model110RadioButton);
      modelVBox.getChildren().add(model200RadioButton);
      
      return modelVBox;
   }
   
   private VBox buildExtraOptionsVBox()
   {
      insuranceCheckBox = new CheckBox("Phone Replacement Insurance for $5 per month");
      hotspotCheckBox = new CheckBox("WiFi HotSpot Capability for $10 per month");
      Label titleLabel = new Label("Select any Extras:");
      
      insuranceCheckBox.setOnAction(event -> updateHasInsurance(insuranceCheckBox.isSelected()));
      hotspotCheckBox.setOnAction(event -> setHasHotspot(hotspotCheckBox.isSelected()));
      
      VBox extraOptionsVBox = new VBox();
      extraOptionsVBox.getChildren().add(titleLabel);
      extraOptionsVBox.getChildren().add(insuranceCheckBox);
      extraOptionsVBox.getChildren().add(hotspotCheckBox);
      
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
      phoneSubTotalTextField.setText("$" + convertAndFormatDoubleToString(cart.getPhoneCost()));
      phoneTaxTextField.setText("$" + convertAndFormatDoubleToString(cart.getPhoneTax()));
      phoneCostTextField.setText("$" + convertAndFormatDoubleToString(cart.getTotalPhoneCost()));
      optionsCostTextField.setText("$" + convertAndFormatDoubleToString(cart.getExtraOptionsCost()));
      planCostTextField.setText("$" + convertAndFormatDoubleToString(cart.getPlanCost()));
      monthlyCostTextField.setText("$" + convertAndFormatDoubleToString(cart.getMonthlyCost()));
      totalCostTextField.setText("$" + convertAndFormatDoubleToString(cart.getTotalCost()));
   }
   
   private String convertAndFormatDoubleToString(double num)
   {
      return String.format("%.2f", num);
   }
}