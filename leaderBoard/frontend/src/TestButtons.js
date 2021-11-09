import 'bootstrap/dist/css/bootstrap.min.css';
import React from 'react';
import ReactDOM from 'react-dom';
import {Button, ButtonGroup, Table} from 'reactstrap';
import axios from 'axios';

class TestButtons extends React.Component{
	constructor () {
		super()
		this.state = {
			testId: 1
		}
		this.updateIndex = this.updateIndex.bind(this)
	}

	updateIndex(e) {
		this.setState({testId: e.target.value})
	}

	updateRanking() {
		const testResult = axios.get(
			'http://127.0.0.1:8000/testResultApp/' + this.state.testId,
			{ example: 'data' },
			{ headers: { 'Content-Type': 'application/json' } }
		);

		testResult.then((response) => {
			const result = response.data;

			var tdChildren = [];
			for (let i = 0; i < result.length; ++i) {
				const newRow = (<tr key={i}>
									<td key={result[i].studentName}>{result[i].studentName}</td>
									<td key={result[i].result}>{result[i].result}</td>
								</tr>);
				tdChildren.push(newRow);
			}

			ReactDOM.render(
				(<Table>
					<thead>
						<tr key="-1">
							<th>Students</th>
							<th>Speed(ms)</th>
						</tr>
					</thead>
					<tbody>
						{tdChildren}
					</tbody>
				</Table>
				),
				document.getElementById('rankings')
			);
		});
	}

	render() {
		this.updateRanking();
		return (
			<ButtonGroup className="mb-2">
				<Button outline value="1" onClick={e=>{this.updateIndex(e, "value")}} autoFocus="autoFocus"> Test1 </Button>
				<Button outline value="2" onClick={e=>{this.updateIndex(e, "value")}}>Test2</Button>
				<Button outline value="3" onClick={e=>{this.updateIndex(e, "value")}}>Test3</Button>
				<Button outline value="4" onClick={e=>{this.updateIndex(e, "value")}}>Test4</Button>
				<Button outline value="5" onClick={e=>{this.updateIndex(e, "value")}}>Test5</Button>
				<Button outline value="6" onClick={e=>{this.updateIndex(e, "value")}}>Test6</Button>
			</ButtonGroup>
		);
	}
}

export default TestButtons;