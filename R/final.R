# ---------------------------------------------------------------------------------
#
#	Interview Code
#	Sales Revenue Prediction
#
#	Author: G. Martin
#	Date: 8JAN2017
#
# ---------------------------------------------------------------------------------

# ---------- Setup ----------

#load rpart library
library(rpart)

#choosed model
modelChoice = c("Linear","Rpart","GLM")
modelType = modelChoice[1]

#set limit on iterations of tuning algorythm
iter_limit = 100
iter_counter = 0

# ---------- Load and Transform data ----------

# load data
filename="C:/Users/874700/xArchive/20180105/Data.csv"
rawdata <- read.csv(file=filename)

# add Date_AsDate
x = substr(rawdata$DateStringYYYYMMDD,1,4)
x = paste(x, "-", sep = "")
x = paste(x, substr(rawdata$DateStringYYYYMMDD,5,6), sep = "")
x = paste(x, "-", sep = "")
x = paste(x, substr(rawdata$DateStringYYYYMMDD,7,8), sep = "")
rawdata$Date_AsDate = as.Date(x)

# add DOW_AsChar
rawdata$DOW_AsChar = as.character(rawdata$Fiscal_dayofWk)

# add Qtr_AsChar
rawdata$Qtr_AsChar = as.character(rawdata$Fiscal_Qtr)

# --- Assign k-fold subsamples ---

# randomly mix up the data
mixdata=rawdata[sample(nrow(rawdata),nrow(rawdata)),]

# create folds vector (for 5 folds)
fold_count = 5
fold = c(0:(nrow(rawdata)-1))
fold = (fold %% fold_count) + 1

# assign folds to mixdata dataframe
mixdata$fold <- fold


# ---------- polyStr_function ----------
polyStr = function(VarName, Order){
	
	#Order must be at least 2
	if(Order < 2){return(VarName)}
	
	#establish string to build
	retStr = ""

	#loop thru from Order, creating a polynomial string
	for(i in Order:1){
		if(i == Order){
			retStr = paste("I(", VarName, "^", i, ")", sep = "")
		} else if(i ==1) {
			retStr = paste(retStr, " + ", VarName, sep = "")
		} else {
			retStr = paste(retStr, " + I(", VarName, "^", i, ")", sep = "")
		}
	}
	
	#return string
	return(retStr)	
}

# ---------- testing function ----------
test_this_formula = function(test_formula, type){
	
	#establish MSE vector
	vec_MSE = vector()
	
	#run thru each test set
	for(i in 1:fold_count){
		
		#establish data sets
		train_data = subset(mixdata, fold!=i) #get train data
		test_data = subset(mixdata, fold==i) #get test data
		
		#establish model
		if(type == "Linear"){
			model <- lm(test_formula, data = train_data)
		} else if(type == "Rpart"){
			model <- rpart(test_formula, data = train_data)
		} else if(type == "GLM"){
			model <- glm(test_formula, data = train_data)
		} else {
			#invalid function
			return(0)
		}
		
		#run prediction
		prediction <- predict(model, newdata = test_data)
		
		#get MSE
		vec_MSE[i] = mean((test_data$SalesRevenue - prediction)^2)
	}
	
	#print out formula and MSE
	x = as.character(format(test_formula))
	print(paste(type, "|", x, "|", mean(vec_MSE)))
	
	#return list object
	ret_list = list(mean(vec_MSE), test_formula, model)
	names(ret_list) = c("MSE","Formula","Model")
	return(ret_list)
}


# ---------- Greedy algorithm ----------

#establish the response variable
rv = "SalesRevenue"

#establish a vector of vnames
vname = vector()
vname[length(vname)+1] = polyStr("Fiscal_Qtr",2)
vname[length(vname)+1] = "Fiscal_Qtr"
vname[length(vname)+1] = "Qtr_AsChar"
vname[length(vname)+1] = "Fiscal_dayofWk"
vname[length(vname)+1] = "DOW_AsChar"
vname[length(vname)+1] = "Daypart"
vname[length(vname)+1] = "HourlyWeather"
vname[length(vname)+1] = "Hour"
vname[length(vname)+1] = polyStr("Hour",2)
vname[length(vname)+1] = "AvgHourlyTemp"
vname[length(vname)+1] = "Date_AsDate"



#create a data frame with these names
ev = data.frame(idx = 1:length(vname), vname)

#establish baseline best model object
best_model_object = list(MSE = 10000000)

# run algorithm
while(nrow(ev)>0){
	
	#increment iteration counter
	iter_counter = iter_counter+ 1

	#establish base formula
	if(is.null(best_model_object$Formula)){
		
		#if best model DNE yet
		base_frm_str = "SalesRevenue ~ "
	} else {
		
		#grab beginning of base model
		base_frm_str = as.character(format(best_model_object$Formula))
		base_frm_str = paste(base_frm_str, " + ")
	}

	#reset added_var_idx
	added_var_idx = 0
	
	#loop through remaining explanatory variables
	for(i in 1:nrow(ev)){
	
		#build formula
		new_ev = as.character(ev$vname[i])
		formula_str = paste(base_frm_str, new_ev)
		this_formula = as.formula(formula_str)

		#test this formula and store results
		this_model_object = test_this_formula(this_formula, modelType)
	
		#compare against the best
		if(this_model_object$MSE < best_model_object$MSE){
	
			best_model_object = this_model_object
			added_var_idx = ev$idx[i]
		}
	}
	
	#check results of this iteration
	if(added_var_idx == 0 || iter_counter == iter_limit){
		
		#stop running if no improvement by clearing the frame
		ev = data.frame()
	} else {

		#remove the used variable
		ev = subset(ev, ev$idx != added_var_idx)	
		print(ev)
	}
}

# ---------- make generic prediction ----------

#copy best model
generic_model = lm(best_model_object$Formula, data = mixdata)

# build generic data frame
Fiscal_Qtr=3
Qtr_AsChar="3"
Date_AsDate=as.Date("2017-07-15")
Fiscal_dayofWk=6
DOW_AsChar="6"
Daypart="Lunch"
HourlyWeather="clear-day"
Hour=12
AvgHourlyTemp=86
generic_data = data.frame(Fiscal_Qtr,Date_AsDate,Fiscal_dayofWk,Daypart,HourlyWeather,Hour,AvgHourlyTemp)

#make prediction
my_pred = predict(generic_model, newdata = generic_data)

#print prediction, model, and summary
print(my_pred)
print(generic_model)
summary(generic_model)


