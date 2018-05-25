<?php

/**************************************
Build PDF
---DESCRIPTION: This function takes an award_id and pulls data from the DB to create a PDF.
	The steps:
		1) Execute a SELECT query in the DB to pull this award_id
		2) Bind the results to variables
		3) Pull the template TEX content from `pdf_builder\pdf_template.txt`
		4) Replace all of the placeholder text in the template with the data from the DB
		5) Create the TEX file from the modified content
		6) Create the PDF from the TEX file
		7) Echo a table of the DB data
		8) Copy the PDF file into the `/pdf_files/` directory
		9) Create links to view PDF or email
		
---INPUT: award_id as a argument in the function
***************************************/
	
	//Build the PDF
	function build_pdf($award_id){
		
		//toggle debug statements that print to page
		$debug = false;
		
		//--------------------------------------------------------------------		
		//set up query
		global $mysqli;
		if (!($stmt = $mysqli->prepare("
		
			SELECT
				A.fk_creator, U.username, A.fk_type, AT.type, 
				A.recipient, A.email, A.biz_name, A.reason,
				A.biz_addr1, A.biz_addr2, A.created, U.name, U.ID
			FROM awards A
			LEFT JOIN users U ON A.fk_creator = U.ID
			LEFT JOIN award_types AT ON A.fk_type = AT.id
			WHERE A.ID = ?
		
		"))) {
				echo "Fetch Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		
		//bind award_id to the query
		if(!($stmt->bind_param("i",$award_id))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}

		//execute the query
		if (!$stmt->execute()) {
			echo "Fetch Execute failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		
		//bind the result to local variables
		if (!$stmt->bind_result(
				$creator_id, $presenter_username, $type_id, $name_of_award,
				$recipient, $rec_email, $biz_name, $reason1,
				$biz_address1, $biz_address2, $presented, $presenter, $presenter_id
			)) {
			echo "Binding output parameters failed: (" . $stmt->errno . ") " . $stmt->error;
		}
		
		//get results
		$stmt->fetch();
		
		//get signature_filename (User_ID.jpg)
		$signature_filename = $presenter_id . '.jpg';
	
		//--------------------------------------------------------------------
		
		//get directories
		$parent_dir = getcwd(); //save parent directory
		chdir($parent_dir . '/pdf_builder'); //go into build directory
		$build_dir = getcwd(); //save build directory (this directory)
		
		//get full filepaths
		$pdf_template_path = $build_dir . '/pdf_template.txt'; //get pdf template filepath
		$signature_path = $parent_dir . '/signature_files/' . $signature_filename; //get signature path
		
		//check if this file exists
		$file_does_exist = file_exists($signature_path);
		
		//if file does not exist, use BLANK.jpg
		if(!$file_does_exist){
			$signature_path = $parent_dir . '/signature_files/BLANK.jpg';
		}
		
		if ($debug) echo "<p>build_dir: $build_dir</p>";
		if ($debug) echo "<p>parent_dir: $parent_dir</p>";
		
		//clear previous building files from this build directory
		shell_exec('rm -f *.aux');
		shell_exec('rm -f *.log');
		shell_exec('rm -f *.pdf');
		shell_exec('rm -f *.tex');
		//--------------------------------------------------------------------
		
		//set tex_contents to the template contents
		$tex_contents = file_get_contents($pdf_template_path);
		$curr_timestamp = date("Y-m-d H:i:s");
		$curr_timestamp = $curr_timestamp . " PST";
		
		if ($debug) echo "<p>Before update: $tex_contents</p><hr>";
		
		//reformat the presented date if valid
		if($presented == 0) $presented = date("Y-m-d H:i:s");
		$presented = date("F j, Y", strtotime($presented));
		
		//replace any instance of empty string with a '-'
		// since latex will fail trying to format an empty string
		if($curr_timestamp == '') $curr_timestamp = '-';
		if($recipient == '') $recipient = '-';
		if($presented == '') $presented = '-'; 
		if($biz_name == '') $biz_name = '-';
		if($biz_address1 == '') $biz_address1 = '-'; 
		if($biz_address2 == '') $biz_address2 = '-';
		if($name_of_award == '') $name_of_award = '-'; 
		if($reason1 == '') $reason1 = '-';
		if($presenter == '') $presenter = '(Name field empty)'; 
		if($signature_path == '') $signature_path = '-';
		
		if ($debug) echo "<p>curr_timestamp: $curr_timestamp</p>";
		if ($debug) echo "<p>recipient: $recipient</p>";
		if ($debug) echo "<p>presented: $presented</p>";
		if ($debug) echo "<p>biz_name: $biz_name</p>";
		if ($debug) echo "<p>biz_address1: $biz_address1</p>";
		if ($debug) echo "<p>biz_address2: $biz_address2</p>";
		if ($debug) echo "<p>name_of_award: $name_of_award</p>";
		if ($debug) echo "<p>reason1: $reason1</p>";
		if ($debug) echo "<p>presenter: $presenter</p>";
		if ($debug) echo "<p>signature_path: $signature_path</p>";
		
		//update tex_contents with values from query
		$tex_contents = str_replace("((timestamp))",$curr_timestamp,$tex_contents);
		$tex_contents = str_replace("((recipient))",$recipient,$tex_contents);
		$tex_contents = str_replace("((presented))",$presented,$tex_contents);
		$tex_contents = str_replace("((biz_name))",$biz_name,$tex_contents);
		$tex_contents = str_replace("((biz_address1))",$biz_address1,$tex_contents);
		$tex_contents = str_replace("((biz_address2))",$biz_address2,$tex_contents);
		$tex_contents = str_replace("((name_of_award))",$name_of_award,$tex_contents);
		$tex_contents = str_replace("((reason1))",$reason1,$tex_contents);
		$tex_contents = str_replace("((presenter))",$presenter,$tex_contents);
		$tex_contents = str_replace("((signature))",$signature_path,$tex_contents);
		
		if ($debug) echo "<p>After update: $tex_contents</p><hr>";
		
		//--------------------------------------------------------------------
		//create and open new TEX file
		$file_prefix = date("YmdHis");
		$texfile = $file_prefix . ".tex";
		$texfile_open = fopen($texfile, "w");

		//write the TEX file and close
		fwrite($texfile_open, $tex_contents);
		fclose($texfile_open);
		//--------------------------------------------------------------------
		//PDF the TEX file
		$exe_pdflatex = shell_exec("/usr/bin/pdflatex " . $texfile);
		
		//see execution details
		if ($debug) echo "<p>pdflatex execution: $exe_pdflatex</p><hr>";
		
		//--------------------------------------------------------------------
		
		//list PDF file created
		$pdf_files = shell_exec('ls *.pdf');
		
		//check if there was an error creating PDF
		if($pdf_files == ''){
			$pdf_file_value = "** Error creating PDF file **";
		} else {
			$pdf_file_value = $pdf_files;
		}
		
		//print table of this award's data
		echo '<table>';
				echo '<tr><th>Field</th><th>Value</th></tr>';
			echo '<tbody>';
				echo '<tr><td><b>Award Recipient</b></td><td>' . $recipient . '</td></tr>';
				echo '<tr><td><b>Recipient Email</b></td><td>' . $rec_email . '</td></tr>';						
				echo '<tr><td><b>Award Date</b></td><td>' . $presented . '</td></tr>';
				echo '<tr><td><b>Name of Company</b></td><td>' . $biz_name . '</td></tr>';
				echo '<tr><td><b>Address of Company</b></td><td>' . $biz_address1 . '</td></tr>';
				echo '<tr><td><b>City Location</b></td><td>' . $biz_address2 . '</td></tr>';			
				echo '<tr><td><b>Name of Award</b></td><td>' . $name_of_award . '</td></tr>';
				echo '<tr><td><b>Reason for Award</b></td><td>' . $reason1 . '</td></tr>';
				echo '<tr><td><b>Presented By</b></td><td>' . $presenter . '</td></tr>';
				echo '<tr><td><b>PDF Filename</b></td><td>' . $pdf_file_value . '</td></tr>';
			echo '</tbody>';
		echo '</table>';
		
		//div for buttons
		echo '<div class="row">';
		
		//If file was created...
		if($pdf_files != '') {
			
			//set the pdf_filename
			$pdf_filename = $file_prefix . '.pdf';
			
			//copy the files to the pdf_files directory
			$copy_src = $pdf_filename;
			$copy_dest = $parent_dir . '/pdf_files/' . $pdf_filename;
			$exe_copy = copy($copy_src, $copy_dest);
			
			if ($debug) echo "<p>Copy Source: $copy_src</p>";
			if ($debug) echo "<p>Copy Destination: $copy_dest</p>";
			
			//--------------------------------------------------------------------

			//link to PDF for viewing
			echo "<a href='pdf_files/$pdf_filename' class='button button-primary four columns'";
			echo " target='_blank'>Preview PDF</a>";
			
			//link for sending email
			echo "<a href='emaildone.php?filename=$pdf_filename";
			echo "&rec_email=$rec_email&filepath=$copy_dest'";
			echo " class='button button-primary four columns'>Send Email</a>";
		}
		
		//link back to dashboard
		echo "<a href='dashboard.php' class='button four columns'>Back to Dashboard</a>";
		echo '</div>';
	}
	
	
/**************************************
Send PDF Email
---DESCRIPTION: This function takes a PDF filename, recipient email, and PDF filepath
		and sends an email to the recipient email with the PDF file attached.
---INPUT:  PDF filename, recipient email, and PDF filepath as function arguments
---REFERENCES:
	https://www.sanwebe.com/2011/01/send-php-mail-with-attachment
	http://php.net/manual/en/features.file-upload.post-method.php

***************************************/
	function send_pdf_email($file_name,$rec_email,$filepath){
		
		//toggle debug statements that print to page
		$debug = false;
		
		if($debug) echo '<p>file_name: '. $file_name . '</p>';
		if($debug) echo '<p>rec_email: '. $rec_email . '</p>';
		if($debug) echo '<p>filepath: '. $filepath . '</p>';
		
		//set file size, and type
		$file_size = 1048576; //file will not be bigger that 90K -- 1MB is safe
		$file_type = 'application/pdf';
		
		$from_email = 'no-reply@kudosizer.com'; //sender email
		$subject = 'You Have Received an Award'; //subject of email
		$message = 'Congratulations on your award! Thanks for using Kudosizer.'; //message body
		
		//read from the uploaded file & base64_encode content for the mail
		$handle = fopen($filepath, "r");
		$content = fread($handle, $file_size);
		
		fclose($handle);
		$encoded_content = chunk_split(base64_encode($content));

			//random chunk of bytes
			$boundary = md5("sanwebe");
			
			//header
			$headers = "MIME-Version: 1.0\r\n"; 
			$headers .= "From:".$from_email."\r\n"; 
			$headers .= "Reply-To: ".$from_email."" . "\r\n";
			$headers .= "Content-Type: multipart/mixed; boundary = $boundary\r\n\r\n"; 
			
			//plain text 
			$body = "--$boundary\r\n";
			$body .= "Content-Type: text/plain; charset=ISO-8859-1\r\n";
			$body .= "Content-Transfer-Encoding: base64\r\n\r\n"; 
			$body .= chunk_split(base64_encode($message)); 
			
			//attachment
			$body .= "--$boundary\r\n";
			$body .="Content-Type: $file_type; name=\"$file_name\"\r\n";
			$body .="Content-Disposition: attachment; filename=\"$file_name\"\r\n";
			$body .="Content-Transfer-Encoding: base64\r\n";
			$body .="X-Attachment-Id: ".rand(1000,99999)."\r\n\r\n"; 
			$body .= $encoded_content; 
		
		//send the email
		$sentMail = mail($rec_email, $subject, $body, $headers);
		
		//output success or failure messages
		if($sentMail){       
			return true;
		}else{
			return false;
		}
	}
?>

